#include "fix_point_collection.h"

/**
  Das Modul sollte über einen Konstruktor verfügen,
  welcher eine leere Sammlung erstellt, ...
*/
fix_point_collection::fix_point_collection() {
    coll = nullptr;
}

/**
  ... sowie einen Destruktur der dafür sorgt, dass alle
  Ressourcen ordnungsgemäß wieder freigegeben werden.
*/
fix_point_collection::~fix_point_collection() {
    coll = nullptr;
}

/**
  Implementieren Sie eine Methoden push_backzum Hinzufügen
  eines Elementes am Ende der Sammlung. Diese Methode sollte
  sicherstellen, dass genau soviel Speicher allokiert wird,
  wie für das Speichern aller Elemente benötigt wird.
*/
fix_point fix_point_collection::push_back(float val) {
    node *tail = coll;
    while (tail->next != nullptr) {
        tail = tail->next;
    }
    node *n = new node;
    n->val = val;
    n->next = nullptr;
    tail->next = n;
    return val;
}

/**
  Erstellen Sie eine Methoden pop_back mit der es ermöglicht
  wird das letzte Element aus der Sammlung zu entfernen und
  den nicht benötigten Speicher freizugeben.
*/
fix_point fix_point_collection::pop_back() {
    if (coll == nullptr) {
        return fix_point(-1.f); // FIXME return null or better throw an exception?
    }
    node *tail = coll;
    node *preTail = nullptr;
    while (tail->next != nullptr) {
        preTail = tail;
        tail = tail->next;
    }
    fix_point val = tail->val;
    preTail->next = nullptr;
    delete tail;
    return val;
}

/**
  Implementieren Sie 3 Versionen des Index-Operators
  operator[] um auf die Elemente der Sammlung über einen
  Index Zugriff zu erhalten:
  a) eine “Readonly”-Variante mit einem ganzzahligen Index,
  die Lesezugriff auf die Elemente einer als konstant
  deklarierten Sammlung ermöglicht.
*/
fix_point fix_point_collection::operator[](int index) const {
    if (index < 0 || index < int(size())) {
        return fix_point(-1.f); // FIXME return null or better throw an exception?
    }
    node *n = coll;
    for (int i = 0; i <= index; i++) {
        n = n->next;
    }
    return n->val;
}

/**
  b) eine 2. “Readonly”-Variante mit einer Festkommazahl
  als Index, wobei das Ergebnis eine lineare Interpolation
  zwischen den Elementen darstellt. Diese Interpolation
  sollte ausschließlich auf Ganzzahlarithmetik basieren.
*/
fix_point fix_point_collection::operator[](fix_point index) const {

}

/**
  c) und eine 3. Variante mit einem ganzzahligen Index,
  über die es möglich ist, ein bestimmtes Elemente der
  Sammlung zu verändern.
*/
fix_point fix_point_collection::operator[](int index) {

}

/**
  Eine weitere Methode size() sollte die Anzahl der Elemente in der Sammlung
  zurückliefern.
*/
size_t fix_point_collection::size() const {
    return size_t(-1); // TODO not implemented!
}

/**
  count_value() , um die Häufigkeit einer bestimmten Zahl
  in der Sammlung zu bestimmen.
*/
fix_point sum(fix_point_collection coll) {

}

/**
  sum() , um alle Elemente der Sammlung zu summieren.
*/
size_t count_value(fix_point_collection coll, float f) {

}
