#include "ooptool.h"

#include <cstdint>
#include <cstdlib>
#include <fstream>
#include <functional>
#include <memory>
#include <sstream>
#include <thread>

// @OOP: Das müssen Sie alles nicht lesen oder verstehen, nur verwenden.

using namespace std;

static const long MAX_FILESIZE = 1073741824; // one GByte, for binary

ooptool_exception::ooptool_exception(const std::string& cause) {
    this->cause = "ooptool exception:: " + cause;
}

ooptool_exception::ooptool_exception(const std::string& cause, int val) {
    this->cause = "ooptool exception:: " + cause + " : " + to_string(val);
}

ooptool_exception::ooptool_exception(const std::string& cause, long val) {
    this->cause = "ooptool exception:: " + cause + " : " + to_string(val);
}

ooptool_exception::ooptool_exception(const std::string& cause,
                                     const std::string& val) {
    this->cause = "ooptool exception:: " + cause + " : " + val;
}

const char* ooptool_exception::what() const noexcept {
    return cause.c_str();
}

// internal, called on error
static ooptool_exception error(const std::string& cause) {
    cerr << "ERROR: " << cause << endl; // ensure something is printed
    return ooptool_exception(cause);
}

// internal, error formatting
// stackoverflow.com/questions/2342162/stdstring-formatting-like-sprintf
// c++14 way, still ugly that the caller needs to use .c_str() on strings
template <typename... Args>
static string format(const std::string& fmt, Args... args) {
    const char* cfmt = fmt.c_str();
    // +1 to accomodate extra space for '\0'
    size_t size = snprintf(nullptr, 0, cfmt, args...) + 1;
    auto buf = make_unique<char[]>(size);
    snprintf(buf.get(), size, cfmt, args...);
    // We don't want the '\0' inside the returned string
    return string(buf.get(), buf.get() + size - 1);
}

bool starts_with(const std::string& s, const std::string& prefix) {
    return equal(prefix.begin(), prefix.end(), s.begin());
}

std::string format(long val, int length, char fill_char) {
    std::ostringstream ostr;
    if (val < 0) { // if negative handle output of '-' and count it
        ostr << '-';
        if (length > 0) {
            length -= 1;
        }
        val *= -1;
    }
    ostr << std::setfill(fill_char) << std::setw(length) << val;
    return ostr.str();
}

// -- general utilities --

// -- file reading --

bool file_exists(const std::string& filename) {
    ifstream f(filename.c_str()); // automatically closed
    return f.good();
}

vector<char> read_bytes(const std::string& filename) {
    ifstream is(filename, ifstream::binary);
    if (!is) {
        const char* s = filename.c_str();
        throw error(format("read_bytes: filename=%s nicht lesbar", s));
    }
    // go to end of file
    is.seekg(0, is.end);
    streamsize length = is.tellg(); // length/size of file
    // go to start of file
    is.seekg(0, is.beg);
    if (length > MAX_FILESIZE || length < 0) {
        const char* s = filename.c_str();
        throw error(format("read_bytes: filename=%s zu gross", s));
    }
    vector<char> buffer(length);
    is.read(buffer.data(), length); // read completely
    if (!is.good()) {
        const char* s = filename.c_str();
        throw error(format("read_bytes: filename=%s Einlesefehler", s));
    }
    is.close();
    return buffer; // should not be copied, move semantics
}

static string COMMENT_PREFIX("#");
vector<string> read_lines(const std::string& filename) {
    ifstream is(filename);
    if (!is) {
        const char* s = filename.c_str();
        throw error(format("read_lines: filename=%s nicht lesbar", s));
    }
    vector<string> lines;
    string line;
    while (getline(is, line)) {
        if (line.empty()) {
            continue;
        }
        if (starts_with(line, COMMENT_PREFIX)) {
            continue;
        }
        lines.push_back(line);
    }
    return lines;
}

// unfortunately, regular expressions let compile time explode
// thus, we parse manually, which is awful
static string CHARS_DELIM(" \t,;'\"\0"); // what are delimiters
static string CHARS_GERMAN_WORDS("abcdefghijklmnopqrstuvwxyz"
                                 "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                                 "0123456789äöüßÄÖÜ"); // what may remain
static string CHARS_INTEGRAL_WORDS("-+0123456789");

// private, words as changeable parameter, for reuse
static void read_accept_str_vec(const string& line, const string& accept,
                                vector<string>& words) {
    size_t prev = 0, pos;
    while ((pos = line.find_first_of(CHARS_DELIM, prev)) != string::npos) {
        if (pos > prev) {
            string word = line.substr(prev, pos - prev);
            if (word.size() > 0 && // nonempty, only of acceptable chars
                word.find_first_not_of(accept) == string::npos) {
                words.push_back(word);
            }
        }
        prev = pos + 1;
    }
    // something remaining, do not forget last match
    string word = line.substr(prev);
    // double that code of the if in the loop
    if (word.size() > 0 && // nonempty, only of acceptable chars
        word.find_first_not_of(accept) == string::npos) {
        words.push_back(word);
    }
}

static vector<string> read_accept_str(const string& line,
                                      const string& accept) {
    vector<string> words;
    read_accept_str_vec(line, accept, words);
    return words;
}

static vector<string> read_accept_file(const string& filename,
                                       const string& accept) {
    vector<string> words;
    for (string line : read_lines(filename)) {
        read_accept_str_vec(line, accept, words);
    }
    return words;
}

vector<string> read_words(const std::string& filename) {
    return read_accept_file(filename, CHARS_GERMAN_WORDS);
}

vector<int> read_ints(const std::string& filename) {
    vector<int> ints;
    for (string iword : read_accept_file(filename, CHARS_INTEGRAL_WORDS)) {
        try {
            int val = stoi(iword);
            ints.push_back(val);
        } catch (const invalid_argument& err) {
            auto s = iword.c_str();
            throw error(format("read_ints: kein int %s, %s", s, err.what()));
        }
    }
    return ints;
}

vector<long> read_longs(const std::string& filename) {
    vector<long> longs;
    for (string lword : read_accept_file(filename, CHARS_INTEGRAL_WORDS)) {
        try {
            long val = stol(lword);
            longs.push_back(val);
        } catch (const invalid_argument& err) {
            auto s = lword.c_str();
            throw error(format("read_longs: kein long %s, %s", s, err.what()));
        }
    }
    return longs;
}

static string CHARS_FLOAT_WORDS("-+0123456789.");
vector<double> read_doubles(const std::string& filename) {
    vector<double> doubles;
    for (string dword : read_accept_file(filename, CHARS_FLOAT_WORDS)) {
        try {
            double val = stod(dword);
            doubles.push_back(val);
        } catch (const invalid_argument& err) {
            auto s = dword.c_str();
            auto e = err.what();
            throw error(format("read_doubles: kein double %s, %s", s, e));
        }
    }
    return doubles;
}

vector<vector<int>> read_2ints(const std::string& filename) {
    vector<vector<int>> intss;
    for (string line : read_lines(filename)) {
        vector<int> row;
        for (string iword : read_accept_str(line, CHARS_INTEGRAL_WORDS)) {
            try {
                int val = stoi(iword);
                row.push_back(val);
            } catch (const invalid_argument& err) {
                auto s = iword.c_str();
                auto e = err.what();
                throw error(format("read_2ints: kein int %s, %s", s, e));
            }
        }
        intss.push_back(row);
    }
    return intss;
}

vector<vector<double>> read_2doubles(const std::string& filename) {
    vector<vector<double>> doubless;
    for (string line : read_lines(filename)) {
        vector<double> row;
        for (string dword : read_accept_str(line, CHARS_FLOAT_WORDS)) {
            try {
                double val = stod(dword);
                row.push_back(val);
            } catch (const invalid_argument& err) {
                auto s = dword.c_str();
                auto e = err.what();
                throw error(format("read_2doubles: kein double %s, %s", s, e));
            }
        }
        doubless.push_back(row);
    }
    return doubless;
}

static bool str2int(string& word, int& val) {
    if (word.size() == 0) {
        return false;
    }
    if (word.find_first_not_of(CHARS_INTEGRAL_WORDS) != string::npos) {
        return false;
    }
    // does not capture +/- within digits
    val = stoi(word);
    return true;
}

// eat whitespace and all following comment lines
static int skip_comments(const vector<char>& raw, int cur) {
    int size = static_cast<int>(raw.size()); // int is sufficient
    if (cur < 0 || cur >= size) {
        return cur;
    }
    while (cur < size && isspace(raw[cur])) {
        cur += 1;
    }
    if (cur >= size) {
        return cur;
    }
    if (cur > 0) {
        if (raw[cur - 1] != '\n') { // must be a new line
            return cur;
        }
    }
    if (raw[cur] == '#') { // comment start in new line
        while (cur < size && raw[cur] != '\n') {
            cur += 1;
        } // run until end of line
        if (cur < size) {
            cur += 1; // skip newline
        }
        return skip_comments(raw, cur); // again
    }
    return cur;
}

// reads a number in a char array and positions cur after the last digit
// returns cur, modifies parameter val
static int read_asciiint(const vector<char>& raw, int cur, int& val) {
    val = 0;
    if (cur < 0) { // already in error state
        return cur;
    }
    cur = skip_comments(raw, cur);
    int size = static_cast<int>(raw.size()); // int is sufficient
    while (cur < size && isspace(raw[cur])) {
        cur += 1;
    }
    if (cur == size) {
        return -1;
    }
    bool valid = false;
    while (cur < size && isdigit(raw[cur])) {
        valid = true;
        val *= 10;
        val += raw[cur] - '0'; // digit to value, guaranteed by the standard
        cur += 1;
    }
    return valid ? cur : -1;
}

// binary pgm, P5
static std::vector<int> read_pgm5(const string& filename) {
    vector<char> raw = read_bytes(filename); // binary format
    if (raw[0] != 'P' || raw[1] != '5') {
        throw error("read_pgm::kein P5???");
    }
    int cur = 2; // we are here
    int width, height, maxbright;
    cur = read_asciiint(raw, cur, width);
    cur = read_asciiint(raw, cur, height);
    cur = read_asciiint(raw, cur, maxbright);
    if (cur == -1) {
        auto s = filename.c_str();
        auto e = "keine Breite/Hoehe/Helligkeit";
        throw error(format("read_pgm5:: filename=%s, %s", s, e));
    }
    // a single whitespace, often '\n'
    if (raw[cur] == '\r') { // can be windows? thus two chars?
        cur += 1;
        if (cur == -1) {
            throw error(format("read_pgm5:: filename=%s, Windows and end?",
                               filename.c_str()));
        }
    }
    if (!isspace(raw[cur])) {
        throw error(format("read_pgm5:: filename=%s, kein Weissraum nach spec",
                           filename.c_str()));
    }
    cur += 1;
    // ab hier binary
    bool twobyte = maxbright >= 256;
    size_t offset = cur;
    size_t no_bytes = raw.size() - offset;
    size_t needed = (twobyte ? 2 : 1) * width * height;
    if (no_bytes != needed) {
        string fmt = "filename=%s, width=%d, height=%d, maxbright=%d,\n";
        fmt = "read_pgm5:: " + fmt;
        fmt += "           no_bytes=%d, needed=%d";
        auto s = filename.c_str();
        throw error(format(fmt, s, width, height, maxbright, no_bytes, needed));
    }
    vector<int> img(needed + 3);
    img[0] = width;
    img[1] = height;
    img[2] = maxbright;
    if (twobyte) {
        for (size_t i = 0; i < needed; i += 1) {
            char high_ch = raw[offset + 2 * i];
            img[i + 3] = reinterpret_cast<unsigned char&>(high_ch) * 256;
            char low_ch = raw[offset + 2 * i + 1];
            img[i + 3] += reinterpret_cast<unsigned char&>(low_ch);
        }
    } else {
        for (size_t i = 0; i < needed; i += 1) {
            char ch = raw[offset + i];
            img[i + 3] = reinterpret_cast<unsigned char&>(ch);
        }
    }
    return img;
}

// ascii/plain pgm, P2
static std::vector<int> read_pgm2(const string& filename) {
    vector<string> raw_lines = read_lines(filename);
    vector<string> lines;
    // no STL remove_if, as the compile time explodes
    for (string line : raw_lines) {
        if (!starts_with(line, "#")) { // ignore comments
            // only nonempty line, empty lines ignored
            if (line.find_first_of(CHARS_GERMAN_WORDS) != string::npos) {
                lines.push_back(line);
            }
        }
    }
    vector<string> words;
    auto lit = lines.begin();
    while (lit != lines.end() && words.size() < 4) {
        if (words.size() == 0) {
            read_accept_str_vec(*lit, CHARS_GERMAN_WORDS, words); // magic
        } else {
            read_accept_str_vec(*lit, CHARS_INTEGRAL_WORDS, words);
        }
        ++lit;
    }
    if (words.size() < 4) {
        throw ooptool_exception("keine PGM-Datei, zu kurz: ", filename);
    }
    // we have enough to identify the file
    if (words[0] != "P2") { // we use plain format
        // for(auto word : words) { cout << word << " "; }; cout << endl;
        throw ooptool_exception("keine PGM-Datei, kein P2-magic: ", filename);
    }
    int width, height, maxbright;
    if (!str2int(words[1], width)) {
        throw ooptool_exception("keine PGM-Datei, Breite fehlt: ", filename);
    }
    if (!str2int(words[2], height)) {
        throw ooptool_exception("keine PGM-Datei, Hoehe fehlt: ", filename);
    }
    if (!str2int(words[3], maxbright)) {
        throw ooptool_exception("keine PGM-Datei, keine maximale Helligkeit",
                                filename);
    }
    // cout << "w=" << width << ", h=" << height;
    // cout << ", mb=" << maxbright << endl;
    vector<int> img;
    img.reserve(width * height + 3);
    img.push_back(width);
    img.push_back(height);
    img.push_back(maxbright);
    words.erase(words.begin(), words.begin() + 4);
    while (lit != lines.end()) {
        read_accept_str_vec(*lit, CHARS_INTEGRAL_WORDS, words);
        for (auto word : words) {
            int val;
            if (!str2int(word, val)) {
                throw ooptool_exception("Keine PGM-Datei, Pixel: ", word);
            }
            img.push_back(val);
        }
        words.clear();
        ++lit;
    }
    if (img.size() != static_cast<unsigned int>(width * height + 3)) {
        throw ooptool_exception("Keine PGM-Datei, falsche Anzahl Pixel: ",
                                static_cast<int>(img.size()));
    }
    return img;
}

std::vector<int> read_pgm(const std::string& filename) {
    ifstream is(filename, ifstream::binary);
    if (!is) {
        auto s = filename.c_str();
        throw error(format("read_pgm: filename=%s nicht lesbar", s));
    }
    // check magic number (P2 or P5)
    vector<char> buffer(2); // identifier has two chars
    is.read(buffer.data(), 2);
    if (!is.good()) {
        auto s = filename.c_str();
        throw error(format("read_pgm: filename=%s Einlesefehler", s));
    }
    is.close();
    if (buffer[0] != 'P') {
        auto s = filename.c_str();
        string msg = "filename=%s magic must start with 'P' not '%c'";
        msg = "read_pgm: " + msg;
        throw error(format(msg, s, buffer[0]));
    }
    // based on magic number chose right reader
    switch (buffer[1]) {
    case '5':
        return read_pgm5(filename);
        // no fall through as there is a return
    case '2':
        return read_pgm2(filename);
        // no fall through as there is a return
    default: {
        auto s = filename.c_str();
        string msg = "filename=%s magic '2' or '5' not '%c'";
        msg = "read_pgm: " + msg;
        throw error(format(msg, s, buffer[1]));
    }
    }
}

static bool is_pgm(const vector<int>& img) {
    size_t imgsize = img.size();
    if (imgsize < 3) {
        cerr << "is_pgm: nicht gross genug" << endl;
        return false;
    }
    if (imgsize != static_cast<size_t>(img[0] * img[1] + 3)) {
        cerr << "is_pgm: falsche Dimension: ";
        cerr << img[0] << "x" << img[1] << endl;
        return false;
    }
    int maxbright = img[2];
    for (size_t idx = 3; idx < imgsize; idx += 1) {
        if (img[idx] > maxbright) {
            cerr << "is_pgm: Pixel zu hell: @" << idx << endl;
            return false;
        }
        if (img[idx] < 0) {
            cerr << "is_pgm: Pixel zu dunkel: @" << idx << endl;
            return false;
        }
    }
    return true;
}

// ascii/plain pgm, P2
static void save_pgm2(const string& filename, const vector<int>& img) {
    ofstream out(filename);
    if (!out.is_open()) {
        throw ooptool_exception("save_pgm, kann nicht schreiben: ", filename);
    }
    out << "P2\n";
    // dimension
    out << img[0] << " " << img[1] << "\n";
    // max brightness
    out << img[2] << "\n";
    // with 10 per line we are below 70 chars if max digits is 6
    int count = 0;
    for (auto it = img.begin() + 3; it != img.end(); ++it) {
        out << *it;
        count += 1;
        if (count % 10 == 0) {
            out << "\n";
        } else {
            out << " ";
        }
    }
    out.close();
}

// binary pgm, P5
static void save_pgm5(const string& filename, const vector<int>& img) {
    ofstream out(filename, ofstream::binary);
    if (!out.is_open()) {
        throw ooptool_exception("save_pgm, kann nicht schreiben: ", filename);
    }
    out << "P5\n";
    // dimension
    out << img[0] << " " << img[1] << "\n";
    // max brightness
    out << img[2];
    // single whitespace
    out << '\n';
    if (img[2] < 256) {
        for (auto it = img.begin() + 3; it != img.end(); ++it) {
            unsigned char b = static_cast<unsigned char>(*it);
            out << b;
        }
    } else { // two byte
        for (auto it = img.begin() + 3; it != img.end(); ++it) {
            unsigned char b1 = static_cast<unsigned char>(*it >> 8);
            unsigned char b2 = static_cast<unsigned char>(*it & 0xff);
            out << b1; // msb first
            out << b2;
        }
    }
    out.close();
}

void save_pgm(const string& filename, const vector<int>& img, bool plain) {
    if (!is_pgm(img)) {
        throw ooptool_exception("save_pgm, keine PGM-Datei: ", filename);
    }
    if (plain) {
        save_pgm2(filename, img);
    } else {
        save_pgm5(filename, img);
    }
}

// avoid include algorithm (reduce compile time)
static bool contains(const vector<string>& svec, const string& ele) {
    for (const string& s : svec) {
        if (s == ele) {
            return true;
        }
    }
    return false;
}

// removes up to two leading dashes from a string
static inline string remove_dashes(string s) {
    if (starts_with(s, "--")) {
        return s.substr(2);
    } else if (starts_with(s, "-")) {
        return s.substr(1);
    }
    return s;
}

argsp_t::argsp_t(int argc, char* argv[]) {
    init(argc, argv);
}

argsp_t::argsp_t(int argc, const char* argv[]) {
    // oh, just make it work, we do not write anyway
    init(argc, const_cast<char**>(argv));
}

// the argsp arguments parser
void argsp_t::init(int argc, char* argv[]) {
    _program = argv[0];
    for (int i = 1; i < argc; i += 1) {
        string arg{argv[i]};
        if (starts_with(arg, "-")) { // flag or option
            arg = remove_dashes(arg);
            auto it = arg.find("=");
            if (it != string::npos) { // with equals sign -> option
                string key = arg.substr(0, it);
                string val = arg.substr(it + 1);
                _options[key] = val;
            } else { // -> flag
                if (!contains(_flags, arg)) {
                    _flags.push_back(arg);
                }
            }
        } else { // positional
            _positionals.push_back(arg);
        }
    }
}

string argsp_t::program() const {
    return _program;
}

bool argsp_t::flag(const string& key) const {
    return contains(_flags, key);
}

size_t argsp_t::no_flags() const {
    return _flags.size();
}

vector<string> argsp_t::flags() const {
    vector<string> ret = _flags; // a copy
    // move semantics prevent second copy
    return ret;
}

bool argsp_t::has_option(const string& key) const {
    return _options.find(key) != _options.end();
}

size_t argsp_t::no_options() const {
    return _options.size();
}

vector<string> argsp_t::options() const {
    vector<string> ret;
    for (auto it : _options) {
        ret.push_back(it.first);
    }
    return ret;
}

std::string argsp_t::option(const std::string& key) const {
    auto it = _options.find(key);
    if (it == _options.end()) {
        throw error(format("argsp::option: no key %s", key.c_str()));
    }
    return it->second;
}

std::string argsp_t::option(const std::string& key,
                            const std::string& defval) const {
    auto it = _options.find(key);
    if (it == _options.end()) {
        return defval;
    }
    return it->second;
}

int argsp_t::int_option(const std::string& key) const {
    auto it = _options.find(key);
    if (it == _options.end()) {
        throw error(format("argsp::int_option: no %s", key.c_str()));
    }
    try {
        size_t idx;
        int val = stoi(it->second, &idx);
        if (it->second[idx] != 0) {
            throw invalid_argument("no just an int");
        }
        return val;
    } catch (const invalid_argument&) { // exception not used
        auto k = key.c_str();
        auto s = it->second.c_str();
        throw error(format("argsp::int_option(%s): no int %s", k, s));
    }
}

int argsp_t::int_option(const std::string& key, int defval) const {
    auto it = _options.find(key);
    if (it == _options.end()) {
        return defval;
    }
    try {
        size_t idx;
        int val = stoi(it->second, &idx);
        if (it->second[idx] != 0) {
            throw invalid_argument("no just an int");
        }
        return val;
    } catch (const invalid_argument&) { // exception not used
        auto msg = "argsp::int_option(%s, %d): no int %s";
        auto k = key.c_str();
        auto s = it->second.c_str();
        throw error(format(msg, k, defval, s));
    }
}

long argsp_t::long_option(const std::string& key) const {
    auto it = _options.find(key);
    if (it == _options.end()) {
        throw error(format("argsp::long_option: no %s", key.c_str()));
    }
    try {
        size_t idx;
        long val = stol(it->second, &idx);
        if (it->second[idx] != 0) {
            throw invalid_argument("no just a long");
        }
        return val;
    } catch (const invalid_argument&) { // exception not used
        auto k = key.c_str();
        auto s = it->second.c_str();
        throw error(format("argsp::long_option(%s): no long %s", k, s));
    }
}

long argsp_t::long_option(const std::string& key, long defval) const {
    auto it = _options.find(key);
    if (it == _options.end()) {
        return defval;
    }
    try {
        size_t idx;
        long val = stol(it->second, &idx);
        if (it->second[idx] != 0) {
            throw invalid_argument("no just a long");
        }
        return val;
    } catch (const invalid_argument&) { // exception not used
        auto k = key.c_str();
        auto s = it->second.c_str();
        throw error(format("argsp::long_option(%s): no long %s", k, s));
    }
}

double argsp_t::double_option(const std::string& key) const {
    auto it = _options.find(key);
    if (it == _options.end()) {
        throw error(format("argsp::double_option: no %s", key.c_str()));
    }
    try {
        size_t idx;
        double val = stod(it->second, &idx);
        if (it->second[idx] != 0) {
            throw invalid_argument("no just a double");
        }
        return val;
    } catch (const invalid_argument&) { // exception not used
        auto k = key.c_str();
        auto s = it->second.c_str();
        throw error(format("argsp::double_option(%s): no double %s", k, s));
    }
}

double argsp_t::double_option(const std::string& key, double defval) const {
    auto it = _options.find(key);
    if (it == _options.end()) {
        return defval;
    }
    try {
        size_t idx;
        double val = stod(it->second, &idx);
        if (it->second[idx] != 0) {
            throw invalid_argument("no just a double");
        }
        return val;
    } catch (const invalid_argument&) { // exception not used
        auto k = key.c_str();
        auto s = it->second.c_str();
        throw error(format("argsp::double_option(%s): no double %s", k, s));
    }
}

vector<string> argsp_t::positionals() const {
    return _positionals; // a copy on purpose
}

size_t argsp_t::no_pos() const {
    // we may cache, but efficiency is not important here
    return _positionals.size();
}

string argsp_t::pos(size_t idx) const {
    if (idx >= _positionals.size()) {
        throw error(format("argsp::pos: no idx %zu", idx));
    }
    return _positionals[idx];
}

string argsp_t::pos(size_t idx, const std::string& defval) const {
    if (idx >= _positionals.size()) {
        return defval;
    }
    return _positionals[idx];
}

vector<int> argsp_t::int_positionals() const {
    vector<int> ret;
    for (size_t idx = 0; idx < _positionals.size(); idx += 1) {
        ret.push_back(int_pos(idx));
    }
    return ret;
}

int argsp_t::int_pos(size_t idx) const {
    if (idx >= _positionals.size()) {
        throw error(format("argsp::int_pos: no idx %zu", idx));
    }
    try {
        size_t lidx;
        int val = stoi(_positionals[idx], &lidx);
        if (_positionals[idx][lidx] != 0) {
            throw invalid_argument("no just an int");
        }
        return val;
    } catch (const invalid_argument&) { // exception not used
        auto s = _positionals[idx].c_str();
        throw error(format("argsp::int_pos(%d): no int %s", idx, s));
    }
}

int argsp_t::int_pos(size_t idx, int defval) const {
    if (idx >= _positionals.size()) {
        return defval;
    }
    try {
        size_t lidx;
        int val = stoi(_positionals[idx], &lidx);
        if (_positionals[idx][lidx] != 0) {
            throw invalid_argument("no just an int");
        }
        return val;
    } catch (const invalid_argument&) { // exception not used
        auto s = _positionals[idx].c_str();
        throw error(format("argsp::int_pos(%zu): no int %s", idx, s));
    }
}

vector<long> argsp_t::long_positionals() const {
    vector<long> ret;
    for (size_t idx = 0; idx < _positionals.size(); idx += 1) {
        ret.push_back(long_pos(idx));
    }
    return ret;
}

long argsp_t::long_pos(size_t idx) const {
    if (idx >= _positionals.size()) {
        throw error(format("argsp::long_pos: no idx %zu", idx));
    }
    try {
        size_t lidx;
        long val = stol(_positionals[idx], &lidx);
        if (_positionals[idx][lidx] != 0) {
            throw invalid_argument("no just a long");
        }
        return val;
    } catch (const invalid_argument&) { // exception not used
        auto s = _positionals[idx].c_str();
        throw error(format("argsp::long_pos(%zu): no long %s", idx, s));
    }
}

long argsp_t::long_pos(size_t idx, long defval) const {
    if (idx >= _positionals.size()) {
        return defval;
    }
    try {
        size_t lidx;
        long val = stol(_positionals[idx], &lidx);
        if (_positionals[idx][lidx] != 0) {
            throw invalid_argument("no just a long");
        }
        return val;
    } catch (const invalid_argument&) { // exception not used
        auto s = _positionals[idx].c_str();
        throw error(format("argsp::long_pos(%zu): no long %s", idx, s));
    }
}

vector<double> argsp_t::double_positionals() const {
    vector<double> ret;
    for (size_t idx = 0; idx < _positionals.size(); idx += 1) {
        ret.push_back(double_pos(idx));
    }
    return ret;
}

double argsp_t::double_pos(size_t idx) const {
    if (idx >= _positionals.size()) {
        throw error(format("argsp::double_pos: no idx %zu", idx));
    }
    try {
        size_t lidx;
        double val = stod(_positionals[idx], &lidx);
        if (_positionals[idx][lidx] != 0) {
            throw invalid_argument("no just a double");
        }
        return val;
    } catch (const invalid_argument&) { // exception not used
        auto s = _positionals[idx].c_str();
        throw error(format("argsp::double_pos(%zu): no double %s", idx, s));
    }
}

double argsp_t::double_pos(size_t idx, double defval) const {
    if (idx >= _positionals.size()) {
        return defval;
    }
    try {
        size_t lidx;
        double val = stod(_positionals[idx], &lidx);
        if (_positionals[idx][lidx] != 0) {
            throw invalid_argument("no just a double");
        }
        return val;
    } catch (const invalid_argument&) { // exception not used
        auto s = _positionals[idx].c_str();
        throw error(format("argsp::double_pos(%zu): no double %s", idx, s));
    }
}

static vector<int> _create_randints(int how_many, int lower, int upper) {
    vector<int> ret(how_many);
    int modulo = (upper - lower) + 1;
    if (modulo < 0) {
        modulo = upper;
    }
    for (int i = 0; i < how_many; i += 1) {
        ret[i] = (static_cast<int>(rand()) % modulo) + lower;
    }
    return ret;
}

vector<int> create_randints(int how_many, int lower, int upper) {
    chrono::high_resolution_clock::time_point beginning =
        chrono::high_resolution_clock::now();
    int seed = beginning.time_since_epoch().count() % 2097152;
    srand(seed);
    return _create_randints(how_many, lower, upper);
}

vector<int> create_same_randints(int how_many, int lower, int upper) {
    srand(1234567); // default seed fixed number
    return _create_randints(how_many, lower, upper);
}

bool is_sorted(vector<int>& a, int& first_error) {
    size_t asize = a.size();
    for (size_t i = 1; i < asize; i += 1) {
        if (a[i - 1] > a[i]) {
            first_error = static_cast<int>(i); // int is sufficient
            return false;
        }
    }
    first_error = 0;
    return true;
}

bool check_sort_one(sort_function sort, int size, bool timing, int verbose) {
    vector<int> a = create_randints(size);
    int first_error;
    if (is_sorted(a, first_error)) {
        if (verbose > 10) {
            cout << "Warnung, ursprüngliches Feld schon sortiert";
        }
    }
    // build sum
    long sum = 0;
    for (int val : a) {
        sum += val;
    }
    Timer timer;
    reset_swaps();
    sort(a);
    int swaps = get_swaps();
    string measure = timer.human_measure();
    if (!is_sorted(a, first_error)) {
        auto fem1 = first_error - 1;
        cout << "Fehler: Feld a[" << a.size() << "] nicht sortiert, ";
        cout << "a[" << fem1 << "]=" << a[fem1] << " > ";
        cout << "a[" << first_error << "]=" << a[first_error] << endl;
        return false;
    }
    // add -sum
    for (int val : a) {
        sum -= val;
    }
    if (sum != 0) { // checksum failed
        cout << "Fehler: Feld a[" << a.size() << "] sortiert, ";
        cout << "aber andere Werte als im ursprünglichen Feld";
        return false;
    }
    if (verbose >= 1) {
        cout << "a[" << setw(8) << size << "]: sorted ";
        if (timing) {
            cout << " " << measure;
        }
        if (swaps > 0) { // assume it is used
            cout << " swaps=" << setw(10) << swaps;
        }
        cout << endl;
    }
    return true;
}

bool check_sort(sort_function sort, bool timing, bool large, int verbose) {
    vector<int> sizes = {10, 100, 1000, 10000, 20000, 40000, 60000};
    for (int size : sizes) {
        if (!check_sort_one(sort, size, timing, verbose)) {
            return false;
        }
    }
    if (large) {
        vector<int> sizes = {80000, 100000, 200000, 400000, 800000, 1000000};
        for (int size : sizes) {
            if (!check_sort_one(sort, size, timing, verbose)) {
                return false;
            }
        }
    }
    return true;
}

int _swaps_counter = 0; // not static, as inlined in header in swap

int get_swaps() {
    return _swaps_counter;
}

int reset_swaps() {
    int ret = _swaps_counter;
    _swaps_counter = 0;
    return ret;
}

Timer::Timer() {
    restart();
}

double Timer::measure() const {
    auto end = chrono::system_clock::now();
    chrono::duration<double> elapsed = end - start;
    return elapsed.count();
}

long Timer::measure_ms() const {
    auto end = chrono::system_clock::now();
    auto elapsed = chrono::duration_cast<chrono::milliseconds>(end - start);
    return static_cast<long>(elapsed.count());
}

long Timer::measure_us() const {
    auto end = chrono::system_clock::now();
    auto elapsed = chrono::duration_cast<chrono::microseconds>(end - start);
    return static_cast<long>(elapsed.count());
}

long Timer::measure_ns() const {
    auto end = chrono::system_clock::now();
    auto elapsed = chrono::duration_cast<chrono::nanoseconds>(end - start);
    return static_cast<long>(elapsed.count());
}

void Timer::restart() {
    start = chrono::system_clock::now();
}

// note, that all three are full and not truncated (modulo)
static string _human_format(long nanos, long mikros, long millis) {
    // check for millis to prevent overflow on 32 bit systems
    if (millis == 0 && nanos <= 999) {
        return format("%3dns", nanos);
    }
    if (millis == 0 && nanos <= 9999) {
        return format("%1d.%1dns", nanos / 1000, (nanos / 100) % 10);
    }
    if (millis == 0 && mikros <= 999) {
        return format("%3dus", mikros);
    }
    if (millis >= 1 && mikros <= 9999) {
        return format("%1d.%1dms", mikros / 1000, (mikros / 100) % 10);
    }
    if (millis <= 999) {
        return format("%3dms", millis);
    }
    if (millis <= 99999) {
        return format("%2d.%1ds", millis / 1000, (millis / 100) % 10);
    }
    long seconds = millis / 1000;
    return format("%ds", seconds);
}

string Timer::human_measure() const {
    long nanos = measure_ns();
    long mikros = measure_us(); // needed for systems with 32 bit long
    long millis = measure_ms(); // needed for systems with 32 bit long
    return _human_format(nanos, mikros, millis);
}

string Timer::human_format(double secs) {
    uint64_t ns = static_cast<uint64_t>(secs * 1000000000);
    uint64_t us = ns / 1000;
    uint64_t ms = us / 1000;
    return _human_format(static_cast<long>(ns), static_cast<long>(us),
                         static_cast<long>(ms));
}

/*void schlafe_ms(int ms) {
    std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}

void schlafe_us(int us) {
    std::this_thread::sleep_for(std::chrono::microseconds(us));
}*/
