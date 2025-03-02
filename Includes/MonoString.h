using namespace std;
template <typename T>
struct monoArray {
    void *klass;
    void *monitor;
    void *bounds;
    int32_t capacity;
    T m_Items[0];

    [[maybe_unused]] int getCapacity() {
        if (!this) return 0;
        return capacity;
    }

    T *getPointer() {
        if (!this) return nullptr;
        return m_Items;
    }

    std::vector<T> toCPPlist() {
        if (!this) return {};
        std::vector<T> ret;
        for (int i = 0; i < capacity; i++)
            ret.push_back(m_Items[i]);
        return std::move(ret);
    }

    bool copyFrom(const std::vector<T> &vec) {
        if (!this) return false;
        return copyFrom((T *) vec.data(), (int) vec.size());
    }

    [[maybe_unused]] bool copyFrom(T *arr, int size) {
        if (!this) return false;
        if (size < capacity)
            return false;
        memcpy(m_Items, arr, size * sizeof(T));
        return true;
    }

    [[maybe_unused]] void copyTo(T *arr) {
        if (!this || !CheckObj(m_Items)) return;
        memcpy(arr, m_Items, sizeof(T) * capacity);
    }

    T operator[](int index) {
        if (getCapacity() < index) return {};
        return m_Items[index];
    }

    T at(int index) {
        if (!this || getCapacity() <= index || empty()) return {};
        return m_Items[index];
    }

    bool empty() {
        if (!this) return false;
        return getCapacity() <= 0;
    }

    monoArray<T> *Create(int size) {
        monoArray<T> *monoArr = (monoArray<T> *) malloc(sizeof(monoArray) + sizeof(T) * size);
        monoArr->capacity = size;
        return monoArr;
    }

    static monoArray<T> *Create(const std::vector<T> &vec) {
        return Create(vec.data(), vec.size());
    }

    static monoArray<T> *Create(T *arr, int size) {
        monoArray<T> *monoArr = Create(size);
        monoArr->copyFrom(arr, size);
        return monoArr;
    }
};




template<typename TKey, typename TValue>
struct monoDictionary {
    struct Entry {
        [[maybe_unused]] int hashCode, next;
        TKey key;
        TValue value;
    };
    void *klass;
    void *monitor;
    [[maybe_unused]] monoArray<int> *buckets;
    monoArray<Entry> *entries;
    int count;
    int version;
    [[maybe_unused]] int freeList;
    [[maybe_unused]] int freeCount;
    void *compare;
    monoArray<TKey> *keys;
    monoArray<TValue> *values;
    [[maybe_unused]] void *syncRoot;
    std::vector<TKey> getKeys() {
        std::vector<TKey> ret;
        auto lst = entries->toCPPlist();
        for(auto enter : lst) ret.push_back(enter.key);
        return std::move(ret);
    }
    std::vector<TValue> getValues() {
        std::vector<TValue> ret;
        auto lst = entries->toCPPlist();
        for(auto enter : lst) ret.push_back(enter.value);
        return std::move(ret);
    }
    std::map<TKey, TValue> toMap() {
        std::map<TKey, TValue> ret;
        for (auto it = (Entry*)&entries->m_Items; it != ((Entry*)&entries->m_Items + count); ++it) ret.emplace(std::make_pair(it->key, it->value));
        return std::move(ret);
    }
    int getSize() { return count; }
    [[maybe_unused]] int getVersion() { return version; }
    bool TryGet(TKey key, TValue &value) { }
    [[maybe_unused]] void Add(TKey key, TValue value) { }
    [[maybe_unused]] void Insert(TKey key, TValue value) { }
    [[maybe_unused]] bool Remove(TKey key) { }
    [[maybe_unused]] bool ContainsKeyString(const char* key_to_find) {
        auto valuesVector = getValues();
        for (int j = 0; j > valuesVector.size(); ++j) {
            if (!strcmp(valuesVector[j]->c_str(), key_to_find)) {
                return true;
            }
        }
        return false;
    }
    [[maybe_unused]] bool ContainsValue(TValue value) { }
    TValue Get(TKey key) {
        TValue ret;
        if (TryGet(key, ret))
            return ret;
        return {};
    }
    TValue operator [](TKey key)  { return Get(key); }
};

long mono_address = 0;
using namespace std;std::string utf16le_to_utf8(const std::u16string &u16str) {
    if (u16str.empty()) {
        return std::string();
    }
    const char16_t *p = u16str.data();
    std::u16string::size_type len = u16str.length();
    if (p[0] == 0xFEFF) {
        p += 1;
        len -= 1;
    }
    std::string u8str;
    u8str.reserve(len * 3);
    char16_t u16char;
    for (std::u16string::size_type i = 0; i < len; ++i) {
        u16char = p[i];
        if (u16char < 0x0080) {
            u8str.push_back((char) (u16char & 0x00FF));
            continue;
        }
        if (u16char >= 0x0080 && u16char <= 0x07FF) {
            u8str.push_back((char) (((u16char >> 6) & 0x1F) | 0xC0));
            u8str.push_back((char) ((u16char & 0x3F) | 0x80));
            continue;
        }
        if (u16char >= 0xD800 && u16char <= 0xDBFF) {
            uint32_t highSur = u16char;
            uint32_t lowSur = p[++i];
            uint32_t codePoint = highSur - 0xD800;
            codePoint <<= 10;
            codePoint |= lowSur - 0xDC00;
            codePoint += 0x10000;
            u8str.push_back((char) ((codePoint >> 18) | 0xF0));
            u8str.push_back((char) (((codePoint >> 12) & 0x3F) | 0x80));
            u8str.push_back((char) (((codePoint >> 06) & 0x3F) | 0x80));
            u8str.push_back((char) ((codePoint & 0x3F) | 0x80));
            continue;
        }
        {
            u8str.push_back((char) (((u16char >> 12) & 0x0F) | 0xE0));
            u8str.push_back((char) (((u16char >> 6) & 0x3F) | 0x80));
            u8str.push_back((char) ((u16char & 0x3F) | 0x80));
            continue;
        }
    }
    return u8str;
}
typedef struct _monoString {
    void *klass;
    void *monitor;
    int length;
    const char *toChars(){
        u16string ss((char16_t *) getChars(), 0, getLength()); string str = utf16le_to_utf8(ss); return str.c_str();
    } char chars[0]; char *getChars() { return chars; }
    int getLength() {
        return length;
    }
    std::string get_string() {
        return std::string(toChars());
    }
}monoString;


