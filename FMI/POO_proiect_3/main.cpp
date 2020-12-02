#include <iostream>
#include <vector>
#include <assert.h>
using namespace std;

template <class K, class V>
class HashNode
{
public:
    HashNode(const K &key, const V &value) :
        key(key), value(value), next(NULL)
    {
    }

    K getKey() const
    {
        return key;
    }

    V getValue() const
    {
        return value;
    }

    void setValue(V value)
    {
        HashNode::value = value;
    }

    HashNode *getNext() const
    {
        return next;
    }

    void setNext(HashNode *next)
    {
        HashNode::next = next;
    }

private:
    K key;
    V value;
    HashNode *next;
};

template <class K>
struct KeyHash
{
    unsigned long operator()(const K& key) const
    {
        return static_cast<unsigned long>(key) % 111;  // am modificat in static_cast din reinterpret_cast; dadea eroare
    }
};

template <class K, class V, class F = KeyHash<K> >
class HashMap;

template <class K, class V>
ostream& operator<< (ostream& out, const HashMap<K, V> &Aux);

template <class K, class V, class F>
class HashMap
{
public:
    HashMap(int Size = 112)
    {
        this->TABLE_SIZE = Size;
        table = new HashNode<K, V>* [Size]();
    }

    ~HashMap()
    {
        for (int i = 0; i < TABLE_SIZE; ++i)
        {
            HashNode<K, V> *entry = table[i];
            while (entry != NULL)
            {
                HashNode<K, V> *prev = entry;
                entry = entry->getNext();
                delete prev;
            }
            table[i] = NULL;
        }
        delete[] table;
    }

   HashMap(const HashMap & Aux)
    {
        this->TABLE_SIZE = Aux.TABLE_SIZE;
        this->table = new HashNode<K, V> *[this->TABLE_SIZE]();

        for (int i = 0; i < this->TABLE_SIZE; i++)
        {
            this->table[i] = Aux.table[i];
        }
    }

    HashMap & operator = (const HashMap& Aux)
    {
        this->TABLE_SIZE = Aux.TABLE_SIZE;
        this->table = Aux.table;
        this->hashFunc = Aux.hashFunc;
        return *this;
    }

    bool get(const K &key, V &value)
    {
        unsigned long hashValue = hashFunc(key);
        HashNode<K, V> *entry = table[hashValue];

        while (entry != NULL)
        {
            if (entry->getKey() == key)
            {
                value = entry->getValue();
                return true;
            }
            entry = entry->getNext();
        }
        return false;
    }

    void put(const K &key, const V &value)
    {
        unsigned long hashValue = hashFunc(key);
        HashNode<K, V> *prev = NULL;
        HashNode<K, V> *entry = table[hashValue];

        while (entry != NULL && entry->getKey() != key)
        {
            prev = entry;
            entry = entry->getNext();
        }
        if (entry == NULL)
        {
            entry = new HashNode<K, V>(key, value);
            if (prev == NULL)
            {
                table[hashValue] = entry;
            }
            else
            {
                prev->setNext(entry);
            }
        }
        else
        {
            entry->setValue(value);
        }
    }

    void remove(const K &key)
    {
        unsigned long hashValue = hashFunc(key);
        HashNode<K, V> *prev = NULL;
        HashNode<K, V> *entry = table[hashValue];

        while (entry != NULL && entry->getKey() != key)
        {
            prev = entry;
            entry = entry->getNext();
        }

        if (entry == NULL)
        {
            return;
        }
        else
        {
            if (prev == NULL)
            {
                table[hashValue] = entry->getNext();
            }
            else
            {
                prev->setNext(entry->getNext());
            }
            delete entry;
        }
    }

    vector <V> ValuesPerKey (const K &key, int *_NrValori)
    {
        unsigned long hashValue = hashFunc(key);
        vector <V> Valori(TABLE_SIZE);
        *_NrValori = 0;

        HashNode <K,V> *entry = table[hashValue];

        while (entry != NULL)
        {
            Valori[(*_NrValori)++] = entry->getValue();
            entry = entry->getNext();
        }
        return Valori;
    }

    int NumberOfDifferentKeys ()
    {
        int NR = 0;
        HashNode <K, V> *entry;
        for (int i = 0; i < TABLE_SIZE; i++)
        {
            entry = table[i];
            while (entry != NULL)
            {
                NR++;
                entry = entry->getNext();
            }
        }
        return NR;
    }

    V operator [] (const K &key)
    {
        unsigned long hashValue = hashFunc(key);
        HashNode <K, V> *entry = table[hashValue];

        while (entry != NULL && entry->getKey() != key)
            entry = entry->getNext();

        if (entry == NULL)
        {
            cout << "Nu exista valoare pentru cheia data";
        }
        else
        {
            return entry->getValue();
        }
    }

    int GetSize()
    {
        return TABLE_SIZE;
    }

    friend ostream& operator<< <>(ostream& out, const HashMap &Aux);

private:
    HashNode<K, V> **table;
    F hashFunc;
    int TABLE_SIZE;
};

template <class K, class V>
ostream& operator << (ostream& out, const HashMap<K, V> &Aux)
{
    out << "Table size = " << Aux.TABLE_SIZE << endl;
    int i;
    HashNode <K, V> *entry;

    for (i = 0; i < Aux.TABLE_SIZE; i++)
    {
        entry = Aux.table[i];
        if (entry != NULL)
        {
            out << "Pentru cheia hash-uita " << i << ": ";
            while (entry != NULL)
            {
                out << entry->getKey() << " ";
                out << entry->getValue() << " ; ";
                entry = entry->getNext();
            }
            out << endl;
        }
    }
}

bool verificare ()
{
    HashMap <int, string> hmap;
    // adaugam in hmap cele 5 perechi de key - value
    hmap.put(1, "A");
    hmap.put(2, "B");
    hmap.put(3, "C");
    hmap.put(4, "D");
    hmap.put(113, "E");

    // 5 perechi
    assert(hmap.NumberOfDifferentKeys() == 5);

    // verificam metodele get si put
    string value;
    hmap.get(4, value);
    assert (value == "D");

    // scoatem valoarea cu cheia "4" si verificam
    hmap.remove(4);

    // mai ramanem cu 4 perechi
    assert (hmap.NumberOfDifferentKeys() == 4);

    // verificarea []
    assert(hmap[1] == "A");

    // verificare =
    HashMap <int, string> h2map;
    assert(h2map.NumberOfDifferentKeys() == 0);
    h2map = hmap;
    assert(h2map.NumberOfDifferentKeys() == 4);

    // verificare copy constructor
    HashMap <int, string> h3map(h2map);
    assert(h3map.NumberOfDifferentKeys() == 4);

    // verificare vector
    vector <string> VecVerif;
    int NrVal;
    VecVerif = hmap.ValuesPerKey(2, &NrVal);
    assert(VecVerif[0] == "B" && VecVerif[1] == "E");

    return true;
}

int main()
{
    bool isWorking;
    isWorking = verificare();
    if (isWorking)
        cout << "Merge!";
    return 0;
}
