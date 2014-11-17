#include "fix_point_collection.h"

/**
  Das Modul sollte über einen Konstruktor verfügen,
  welcher eine leere Sammlung erstellt, ...
*/
fix_point_collection::fix_point_collection() {
    m_size = 0;
}

/**
  ... sowie einen Destruktur der dafür sorgt, dass alle
  Ressourcen ordnungsgemäß wieder freigegeben werden.
*/
fix_point_collection::~fix_point_collection() {
    delete[] m_coll;
}

/**
  Implementieren Sie eine Methoden push_backzum Hinzufügen
  eines Elementes am Ende der Sammlung. Diese Methode sollte
  sicherstellen, dass genau soviel Speicher allokiert wird,
  wie für das Speichern aller Elemente benötigt wird.
*/
fix_point fix_point_collection::push_back(float val) {
    node *newNode = new node;
    newNode->val = new fix_point(val);
    newNode->next = m_coll;
    m_coll = newNode;
    m_size++;
}

/**
  Erstellen Sie eine Methoden pop_back mit der es ermöglicht
  wird das letzte Element aus der Sammlung zu entfernen und
  den nicht benötigten Speicher freizugeben.
*/
fix_point fix_point_collection::pop_back() {
    if (m_coll == nullptr) {
        return -1111.f; // FIXME return null or better throw an exception?
    }
    fix_point fp = *m_coll->val;
    node *oldNode = m_coll;
    m_coll = m_coll->next;
    delete oldNode;
    m_size--;
    return fp;
}

/**
  Implementieren Sie 3 Versionen des Index-Operators
  operator[] um auf die Elemente der Sammlung über einen
  Index Zugriff zu erhalten:
  a) eine “Readonly”-Variante mit einem ganzzahligen Index,
  die Lesezugriff auf die Elemente einer als konstant
  deklarierten Sammlung ermöglicht.
*/
const fix_point& fix_point_collection::operator[](int index) const {
    if (index < 0 || m_size <= index) {
        return *(new fix_point(-1111.f)); // FIXME return null or better throw an exception?
    }
    node *n = m_coll;
    index++;
    while (index < m_size) {
//    while (n != nullptr) {
        n = n->next;
        index++;
    }
    return *n->val;
}

/**
  b) eine 2. “Readonly”-Variante mit einer Festkommazahl
  als Index, wobei das Ergebnis eine lineare Interpolation
  zwischen den Elementen darstellt. Diese Interpolation
  sollte ausschließlich auf Ganzzahlarithmetik basieren.
*/
fix_point fix_point_collection::operator[](fix_point index) const {
    if (float(index) < 0.f || float(m_size-1) < float(index)) {
        return fix_point(-1111.f); // FIXME return null or better throw an exception?
    }
    int le = index.floor();
    int ri = le + 1;
    fix_point f = index.frac();
    return (fix_point(1.f) - f) * (*this)[le] + f * (*this)[ri];
}

/**
  c) und eine 3. Variante mit einem ganzzahligen Index,
  über die es möglich ist, ein bestimmtes Elemente der
  Sammlung zu verändern.
*/
fix_point& fix_point_collection::operator[](int index) {

    // TODO
    // if the pointer solution is alright -> use delegation for one of the two twin methods

    if (index < 0 || m_size <= index) {
//        return fix_point(-1111.f); // FIXME return null or better throw an exception?
        fix_point f = fix_point(-1111.f); // FIXME return null or better throw an exception?
        return f;
//        return new fix_point(-1111.f); // FIXME return null or better throw an exception?
    }
    node *n = m_coll;
    index++;
    while (index < m_size) {
//    while (n != nullptr) {
        n = n->next;
        index++;
    }
    return *n->val;

//    return fix_point(-0.123459f);
//    return *(new fix_point(-0.123459f));
}

/**
  Eine weitere Methode size() sollte die Anzahl der Elemente in der Sammlung
  zurückliefern.
*/
size_t fix_point_collection::size() const {
    return m_size;
}

/**
  count_value() , um die Häufigkeit einer bestimmten Zahl
  in der Sammlung zu bestimmen.
*/
size_t count_value(fix_point_collection &coll, float f) {
    int count = 0;
    for (int i = 0; i < coll.size(); i++) {
        if (coll[i] == f) {
            count++;
        }
    }
    return count;
}

/**
  sum() , um alle Elemente der Sammlung zu summieren.
*/
fix_point sum(fix_point_collection &coll) {
    fix_point sum = fix_point(0.f);
    for (int i = 0; i < coll.size(); i++) {
        sum += coll[i];
//        sum += *coll[i];
    }
    return sum;
//    return fix_point(-0.123459f);
}
