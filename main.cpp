#include <iostream>
#include"string.h"

class GeneratorIDUnic {
private:
    static GeneratorIDUnic *copie;
    uint32_t id;
    GeneratorIDUnic();

public:
    static GeneratorIDUnic *instanta();
    uint32_t next();
};

GeneratorIDUnic* GeneratorIDUnic::copie = 0;
GeneratorIDUnic::GeneratorIDUnic() : id(0) {}

uint32_t GeneratorIDUnic::next() {
    return id ++;
}

GeneratorIDUnic *GeneratorIDUnic::instanta() {
    if (!copie)
        copie = new GeneratorIDUnic();

    return copie;
}

template <typename T> class Lista {
private:
    T* ptr;
    int size;

public:
    Lista(T* objInit);
    void adauga(T* el);
    void afiseaza() const;
    T get(int i);
};

template <typename T> Lista<T>::Lista(T* objInit)
{
    ptr = (T*) malloc(sizeof(T));
    ptr = objInit;
    size = 1;
}

template <typename T> void Lista<T>::afiseaza() const
{
    for (int i = 0; i < size; i++) {
        ptr[i].getProductie()->afiseaza();
        std::cout << std::endl;
    }
}

template <typename T> void Lista<T>::adauga(T* el)
{
    size ++;
    ptr = (T*) realloc(ptr, sizeof(T) * size);
    ptr[size - 1] = *el;
}

template <typename T> T Lista<T>::get(int i)
{
    return ptr[i];
}

class Productie {
protected:
    uint32_t id;
    std::string titlu;
    std::string numeRegizor;
    int anAparitie;
    unsigned int durataMinute;

public:
    Productie(const std::string titlu, const std::string numeRegizor, int anAparitie, unsigned int durataMinute);

    Productie();

    ~Productie();

    Productie& operator=(const Productie &rhs);

    static int getId();

    std::string getTitlu() const;

    void setTitlu(std::string titlu);

    std::string getNumeRegizor() const;

    void setNumeRegizor(std::string numeRegizor);

    int getAnAparitie() const;

    void setAnAparitie(int anAparitie);

    int getDurataMinute() const;

    void setDurataMinute(unsigned int durataMinute);

    virtual Productie* cloneaza() const = 0;

    virtual void afiseaza() const = 0;
};

Productie::Productie(const std::string titlu, const std::string numeRegizor, int anAparitie, unsigned int durataMinute)
{
    this->id = GeneratorIDUnic::instanta()->next();
    this->titlu = titlu;
    this->numeRegizor = numeRegizor;
    this->anAparitie = anAparitie;
    this->durataMinute = durataMinute;
}

Productie::Productie()
{
    titlu = "";
    numeRegizor = "";
    anAparitie = 0;
    durataMinute = 0;
}

Productie::~Productie() = default;

Productie& Productie::operator=(const Productie &rhs)
{
    this->titlu = rhs.titlu;
    this->numeRegizor = rhs.numeRegizor;
    this->anAparitie = rhs.anAparitie;
    this->durataMinute = rhs.durataMinute;

    return *this;
}

std::string Productie::getTitlu() const
{
    return titlu;
}

void Productie::setTitlu(std::string titlu)
{
    this->titlu = titlu;
}

std::string Productie::getNumeRegizor() const
{
    return numeRegizor;
}

void Productie::setNumeRegizor(std::string numeRegizor)
{
    this->numeRegizor = numeRegizor;
}

int Productie::getAnAparitie() const
{
    return anAparitie;
}

void Productie::setAnAparitie(int anAparitie)
{
    this->anAparitie = anAparitie;
}

int Productie::getDurataMinute() const
{
    return durataMinute;
}

void Productie::setDurataMinute(unsigned int durataMinute)
{
    this->durataMinute = durataMinute;
}

class FilmDocumentar : public Productie {
public:
    FilmDocumentar(const std::string titlu, const std::string numeRegizor, int anAparitie, unsigned int durataMinute)
    : Productie(titlu, numeRegizor, anAparitie, durataMinute) {}

    FilmDocumentar() : Productie() {}

    void afiseaza() const override {
        std::cout << this->id << " - Filmul documentar " << this->titlu << ", regizor: "
                  << this->numeRegizor << ". An aparitie: " << this->anAparitie
                  << ". Durata: " << this->durataMinute << " minute";
    }

    FilmDocumentar* cloneaza() const override
    {
        FilmDocumentar* f = new FilmDocumentar(titlu, numeRegizor, anAparitie, durataMinute);

        return f;
    }
};

class FilmAnimatie : public Productie {
public:
    FilmAnimatie(const std::string titlu, const std::string numeRegizor, int anAparitie, unsigned int durataMinute)
    : Productie(titlu, numeRegizor, anAparitie, durataMinute) {}

    FilmAnimatie() : Productie() {}

    void afiseaza() const override {
        std::cout << this->id << " - Filmul de animatie " << this->titlu << ", regizor: "
                  << this->numeRegizor << ". An aparitie: " << this->anAparitie
                  << ". Durata: " << this->durataMinute << " minute";
    }

    FilmAnimatie* cloneaza() const override
    {
        FilmAnimatie* f = new FilmAnimatie(titlu, numeRegizor, anAparitie, durataMinute);

        return f;
    }
};

class FilmFictiune : public Productie {
public:
    FilmFictiune(const std::string titlu, const std::string numeRegizor, int anAparitie, unsigned int durataMinute)
    : Productie(titlu, numeRegizor, anAparitie, durataMinute) {}

    FilmFictiune() : Productie() {}

    void afiseaza() const override {
        std::cout << this->id << " - Filmul de fictiune " << this->titlu << ", regizor: "
                  << this->numeRegizor << ". An aparitie: " << this->anAparitie
                  << ". Durata: " << this->durataMinute << " minute";
    }

    FilmFictiune* cloneaza() const override
    {
        FilmFictiune* f = new FilmFictiune(titlu, numeRegizor, anAparitie, durataMinute);

        return f;
    }

};

class FilmFactory {
private:
    Productie* productie;

public:
    FilmFactory(const std::string type, const std::string titlu, const std::string numeRegizor, int anAparitie, unsigned int durataMinute)
    {
        if (type == "FilmDocumentar")
        {
            productie = new FilmDocumentar(titlu, numeRegizor, anAparitie, durataMinute);
        }

        else if (type == "FilmAnimatie")
        {
            productie = new FilmAnimatie(titlu, numeRegizor, anAparitie, durataMinute);
        }

        else if (type == "FilmFictiune")
        {
            productie = new FilmFictiune(titlu, numeRegizor, anAparitie, durataMinute);
        }

        else
        {
            productie = NULL;
        }
    }

    FilmFactory(const std::string type = "")
    {
        if (type == "FilmDocumentar")
        {
            productie = new FilmDocumentar();
        }

        else if (type == "FilmAnimatie")
        {
            productie = new FilmAnimatie();
        }

        else if (type == "FilmFictiune")
        {
            productie = new FilmFictiune();
        }

        else
        {
            productie = NULL;
        }
    }

    ~FilmFactory()
    {
        if (productie) {
            delete productie;
            productie = NULL;
        }
    }

    Productie* getProductie() { return productie; }
};

template <typename T> void auAcelasiRegizor(T* x, T* y)
{
    if (x->getNumeRegizor() == y->getNumeRegizor())
        std::cout << "Filmele au acelasi regizor!" << std::endl;
}

template<>
void auAcelasiRegizor(FilmAnimatie* x, FilmAnimatie* y)
{
    if (x->getNumeRegizor() == y->getNumeRegizor())
        std::cout << "Cele doua animatii au acelasi producator!" << std::endl;
}

int main()
{
    Lista<FilmFactory> L(new FilmFactory("FilmDocumentar", "Documentar despre Programare", "John Doe", 2003, 90));
    L.adauga(new FilmFactory("FilmAnimatie", "Alba ca Zapada", "John Smith", 2009, 70));
    L.adauga(new FilmFactory("FilmAnimatie", "Alice in Tara Minunilor", "Steve Jobs", 2019, 60));
    L.afiseaza();
    FilmAnimatie* clona = dynamic_cast<FilmAnimatie*>(L.get(1).getProductie())->cloneaza();
    clona->afiseaza();
    FilmAnimatie* clona2 = dynamic_cast<FilmAnimatie*>(L.get(2).getProductie())->cloneaza();
    std::cout << std::endl;
    auAcelasiRegizor<FilmAnimatie>(clona, clona2);
    return 0;
}
