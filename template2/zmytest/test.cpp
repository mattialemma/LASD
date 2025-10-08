/* ************************************************************************** */
#include <iostream>

#include "../list/list.hpp"
#include "../vector/vector.hpp"
#include "../zlasdtest/container/container.hpp"
#include "../zlasdtest/container/traversable.hpp"
#include "../zlasdtest/container/testable.hpp"
#include "../zlasdtest/container/dictionary.hpp"
#include "../zlasdtest/container/linear.hpp"
#include "../zlasdtest/container/mappable.hpp"

#include "../zlasdtest/vector/vector.hpp"
#include "../zlasdtest/list/list.hpp"
#include "../zlasdtest/set/set.hpp"

#include "../set/lst/setlst.hpp"
#include "../set/vec/setvec.hpp"
#include "../zlasdtest/set/set.hpp"
#include "../zlasdtest/heap/heap.hpp"
#include "../zlasdtest/pq/pq.hpp"


#include "../set/lst/setlst.hpp"
#include "../set/vec/setvec.hpp"

#include "../heap/vec/heapvec.hpp"
#include "../pq/heap/pqheap.hpp"
using namespace lasd;

using namespace std;

namespace mytest {

// Insert PQM
template <typename Data>
void InsertPQM(uint & testnum, uint & testerr, lasd::PQ<Data> & pq, const Data & val) {
    testnum++;
    bool tst = true;
    try {
        std::cout << " " << testnum << " Insert on the priority queue of the value \"" << val << "\": ";
        pq.Insert(std::move(val));
        std::cout << "Correct!" << std::endl;
    } catch(std::exception & exc) {
        std::cout << "\"" << exc.what() << "\": " << "Error!" << std::endl;
        tst = false;
    }
    testerr += (1 - (uint) tst);
}

// Change PQM
template <typename Data>
void ChangePQM(uint & testnum, uint & testerr, lasd::PQ<Data> & pq, ulong idx, const Data & val) {
    testnum++;
    bool tst = true;
    try {
        std::cout << " " << testnum << " Change the value \"" << pq[idx] << "\" at index << \"" << idx << "\" to the value \"" << val << "\" in the priority queue: ";
        pq.Change(idx, std::move(val));
        std::cout << "Correct!" << std::endl;
    } catch(std::exception & exc) {
        std::cout << "\"" << exc.what() << "\": " << "Error!" << std::endl;
        tst = false;
    }
    testerr += (1 - (uint) tst);
}

// List<int> Test
template <typename Data>
void InsertAtBackM(uint & testnum, uint & testerr, lasd::List<Data> & lst, bool chk, const Data & val) {
    bool tst;
    testnum++;
    try {
        std::cout << " " << testnum << " (" << testerr << ") Insert at the back of the list the value \"" << val << "\": ";
        lst.InsertAtBack(move(val));
        std::cout << ((tst = chk) ? "Correct" : "Error") << "!" << std::endl;
    } catch(std::exception & exc) {
        std::cout << "\"" << exc.what() << "\": " << ((tst = !chk) ? "Correct" : "Error") << "!" << std::endl;
    }
    testerr += (1 - (uint) tst);
}

// Sort
template <typename Data>
void Sort(uint & testnum, uint & testerr, lasd::SortableLinearContainer<Data> & con, lasd::SortableLinearContainer<Data> &  c2, bool chk) {
    bool tst;
    testnum++;
    try {
        std::cout << " " << testnum << " (" << testerr << ") Sorting Array ";
        con.Sort();

        std::cout << ((tst = ((con == c2) == chk)) ? "Correct" : "Error") << "!" << std::endl;
    } catch(std::out_of_range & exc) {

        std::cout << exc.what() << "\": " << ((tst = !chk) ? "Correct" : "Error") << "!" << std::endl;
    }  catch(std::exception & exc) {
        tst = false;
        std::cout << std::endl << "Wrong exception: " << exc.what() << "!" << std::endl;
    }
    testerr += (1 - (uint) tst);
}

// Clear
void Clear(uint & testnum, uint & testerr,  lasd::ClearableContainer & con) {
    bool tst;
    testnum++;
    std::cout << " " << testnum << " (" << testerr << ") Clearing the container: ";
    con.Clear();
    std::cout << ((tst = (con.Empty())) ? "Correct" : "Error") << "!" << std::endl;
    testerr += (1 - (uint) tst);
}

// InsertAtFrontM
template <typename Data>
void InsertAtFrontM(uint & testnum, uint & testerr, lasd::List<Data> & lst, bool chk, const Data & val) {
    bool tst;
    testnum++;
    try {
        std::cout << " " << testnum << " (" << testerr << ") Insert at the front of the list the value \"" << val << "\": ";
        lst.InsertAtFront(move(val));
        std::cout << ((tst = chk) ? "Correct" : "Error") << "!" << std::endl;
    } catch(std::exception & exc) {
        std::cout << "\"" << exc.what() << "\": " << ((tst = !chk) ? "Correct" : "Error") << "!" << std::endl;
    }
    testerr += (1 - (uint) tst);
}

/* ***************************************************************** */
// - - - - - -   - - - - - -  TEMPLATE 1 - - - - - -   - - - - - -  //
/* ******************************************************************/

// Vector<int> Test
void testVectorInt(uint & testnum, uint & testerr) {
    uint loctestnum = 0, loctesterr = 0;
    cout << endl << "Begin of Vector<int> Test:" << endl;
    try {
        {
            cout << endl << "Begin of empty Vector<int> Test:" << endl;

            lasd::SortableVector<int> vec;
            lasd::SortableVector<int> vec2;
            vec2 = vec;
            Size(loctestnum, loctesterr, vec, true, 0);
            Size(loctestnum, loctesterr, vec, false, 7);
            Empty(loctestnum, loctesterr, vec, true);
            EqualVector(loctestnum, loctesterr, vec, vec2, true);
            Traverse(loctestnum, loctesterr, vec, true, &TraversePrint<int>);

            SetBack(loctestnum, loctesterr, vec, false, 1);
            SetAt(loctestnum, loctesterr, vec, false, 1, 0);
            SetFront(loctestnum, loctesterr, vec, false, 1);

            GetBack(loctestnum, loctesterr, vec, false, 0);
            GetFront(loctestnum, loctesterr, vec, false, 0);
            GetAt(loctestnum, loctesterr, vec, false, 2, 0);

            Exists(loctestnum, loctesterr, vec, false, 0);

            Fold(loctestnum, loctesterr, vec, true, &FoldAdd<int>, 0, 0);
            FoldPreOrder(loctestnum, loctesterr, vec, true, &FoldAdd<int>, 0, 0);
            FoldPostOrder(loctestnum, loctesterr, vec, true, &FoldAdd<int>, 0, 0);

            Traverse(loctestnum, loctesterr, vec, true, &TraversePrint<int>);
            TraversePreOrder(loctestnum, loctesterr, vec, true, &TraversePrint<int>);
            TraversePostOrder(loctestnum, loctesterr, vec, true, &TraversePrint<int>);

            Map(loctestnum, loctesterr, vec, true, &MapIncrement<int>);
            MapPreOrder(loctestnum, loctesterr, vec, true, &MapIncrement<int>);
            MapPostOrder(loctestnum, loctesterr, vec, true, &MapIncrement<int>);

            lasd::SortableVector<int> chk;
            Sort(loctestnum, loctesterr, vec, chk, true);
            Clear(loctestnum, loctesterr, vec);

            cout  << "End of empty Vector<int> Test:" << endl;

        }
        {
            cout << endl << "Begin of  Vector<int> Test:" << endl;

            lasd::SortableVector<int> vec(3);
            Traverse(loctestnum, loctesterr, vec, true, &TraversePrint<int>);
            Empty(loctestnum, loctesterr, vec, false);
            Size(loctestnum, loctesterr, vec, true, 3);

            SetAt(loctestnum, loctesterr, vec, true, 0, 7);
            SetAt(loctestnum, loctesterr, vec, true, 1, 4);
            SetAt(loctestnum, loctesterr, vec, true, 2, 2);

            GetFront(loctestnum, loctesterr, vec, true, 7);
            GetBack(loctestnum, loctesterr, vec, true, 2);
            GetAt(loctestnum, loctesterr, vec, true, 1, 4);

            SetFront(loctestnum, loctesterr, vec, true, 5);
            SetBack(loctestnum, loctesterr, vec, true, 9);

            Exists(loctestnum, loctesterr, vec, true, 9);
            Exists(loctestnum, loctesterr, vec, true, 4);
            Exists(loctestnum, loctesterr, vec, true, 5);
            Exists(loctestnum, loctesterr, vec, false, 104);

            Traverse(loctestnum, loctesterr, vec, true, &TraversePrint<int>);
            TraversePostOrder(loctestnum, loctesterr, vec, true, &TraversePrint<int>);
            TraversePreOrder(loctestnum, loctesterr, vec, true, &TraversePrint<int>);

            Fold(loctestnum, loctesterr, vec, true, &FoldAdd<int>, 0, 18);
            FoldPostOrder(loctestnum, loctesterr, vec, true, &FoldMultiply<int>, 3, 540);
            FoldPreOrder(loctestnum, loctesterr, vec, true, &FoldAdd<int>, 0, 18);

            Map(loctestnum, loctesterr, vec, true, &MapIncrement<int>);
            MapPreOrder(loctestnum, loctesterr, vec, true, &MapIncrement<int>);
            MapPostOrder(loctestnum, loctesterr, vec, true, &MapIncrement<int>);

            lasd::SortableVector<int> chk(vec);
            Sort(loctestnum, loctesterr, vec, chk, false);
            chk.Sort();
            Sort(loctestnum, loctesterr, vec, chk, true);

            TraversePreOrder(loctestnum, loctesterr, vec, true, &TraversePrint<int>);
            TraversePostOrder(loctestnum, loctesterr, vec, true, &TraversePrint<int>);

            vec.Resize(2);
            FoldPostOrder(loctestnum, loctesterr, vec, true, &FoldMultiply<int>, 1, 56);

            lasd::SortableVector<int> mv(move(vec));
            TraversePostOrder(loctestnum, loctesterr, mv, true, &TraversePrint<int>);

            Clear(loctestnum, loctesterr, mv);
        }
    } catch(...) {
        loctestnum++;
        loctesterr++;
        cout << endl << "Unmanaged error! " << endl;
    }
    cout << "End of Vector<int> Test! (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << endl;
    testnum += loctestnum;
    testerr += loctesterr;
}

// Vector<double> Test
void testVectorDouble(uint & testnum, uint & testerr) {
    uint loctestnum = 0, loctesterr = 0;
    cout << endl << "Begin of Vector<double> Test:" << endl;
    try {
        lasd::SortableVector<double> vec(3);
        Empty(loctestnum, loctesterr, vec, false);
        Size(loctestnum, loctesterr, vec, true, 3);

        SetAt(loctestnum, loctesterr, vec, true, 0, 1.2);
        SetAt(loctestnum, loctesterr, vec, true, 1, 5.7);
        SetAt(loctestnum, loctesterr, vec, true, 2, 8.9);

        SetBack(loctestnum, loctesterr, vec, true, 1.2);
        SetFront(loctestnum, loctesterr, vec, true, 6.5);

        GetFront(loctestnum, loctesterr, vec, false, 0.0);
        GetFront(loctestnum, loctesterr, vec, true, 6.5);
        GetBack(loctestnum, loctesterr, vec, true, 1.2);
        GetAt(loctestnum, loctesterr, vec, true, 1, 5.7);

        Exists(loctestnum, loctesterr, vec, true, 6.5);
        Exists(loctestnum, loctesterr, vec, true, 1.2);
        Exists(loctestnum, loctesterr, vec, true, 5.7);

        Traverse(loctestnum, loctesterr, vec, true, &TraversePrint<double>);
        TraversePostOrder(loctestnum, loctesterr, vec, true, &TraversePrint<double>);
        TraversePreOrder(loctestnum, loctesterr, vec, true, &TraversePrint<double>);

        Fold(loctestnum, loctesterr, vec, true, &FoldAdd<double>, 0.0, 13.399999999999999);
        FoldPreOrder(loctestnum, loctesterr, vec, true, &FoldAdd<double>, 0.0, 13.399999999999999);
        FoldPostOrder(loctestnum, loctesterr, vec, true, &FoldMultiply<double>, 1.0, 44.46);

        Map(loctestnum, loctesterr, vec, true, &MapIncrement<double>);
        MapPreOrder(loctestnum, loctesterr, vec, true, &MapIncrement<double>);
        MapPostOrder(loctestnum, loctesterr, vec, true, &MapIncrement<double>);

        lasd::SortableVector<double> chk(vec);
        chk.Sort();
        Sort(loctestnum, loctesterr, vec, chk, true);
        TraversePostOrder(loctestnum, loctesterr, vec, true, &TraversePrint<double>);       
        TraversePreOrder(loctestnum, loctesterr, vec, true, &TraversePrint<double>);

        vec.Resize(2);
        FoldPostOrder(loctestnum, loctesterr, vec, true, &FoldAdd<double>, 1, 13);

        Clear(loctestnum, loctesterr, vec);

    } catch(...) {
        loctestnum++;
        loctesterr++;
        cout << endl << "Unmanaged error! " << endl;
    }
    cout << "End of Vector<double> Test! (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << endl;
    testnum += loctestnum;
    testerr += loctesterr;
}

// Vector<string> Test
void testVectorString(uint & testnum, uint & testerr) {
    uint loctestnum = 0, loctesterr = 0;
    cout << endl << "Begin of Vector<string> Test:" << endl;
    try {
        lasd::SortableVector<string> vec(2);

        Size(loctestnum, loctesterr, vec, false, 4);
        Empty(loctestnum, loctesterr, vec, false);
        Size(loctestnum, loctesterr, vec, true, 2);

        SetAt(loctestnum, loctesterr, vec, true, 0, string("B"));
        SetAt(loctestnum, loctesterr, vec, true, 1, string("A"));

        GetFront(loctestnum, loctesterr, vec, true, string("B"));
        GetBack(loctestnum, loctesterr, vec, true, string("A"));
        GetAt(loctestnum, loctesterr, vec, true, 1, string("A"));
        GetAt(loctestnum, loctesterr, vec, false, 7, string("A"));

        Exists(loctestnum, loctesterr, vec, true, string("A"));
        Exists(loctestnum, loctesterr, vec, true, string("B"));
        Exists(loctestnum, loctesterr, vec, false, string("C"));

        SetFront(loctestnum, loctesterr, vec, true, string("B"));
        SetBack(loctestnum, loctesterr, vec, true, string("P"));

        MapPreOrder(loctestnum, loctesterr, vec, true, [](string & str) {
            MapStringAppend(str, string(" "));
        });

        Traverse(loctestnum, loctesterr, vec, true, &TraversePrint<string>);
        TraversePreOrder(loctestnum, loctesterr, vec, true, &TraversePrint<string>);
        TraversePostOrder(loctestnum, loctesterr, vec, true, &TraversePrint<string>);

        Fold(loctestnum, loctesterr, vec, true, &FoldStringConcatenate, string("X"), string("XB P "));
        FoldPreOrder(loctestnum, loctesterr, vec, true, &FoldStringConcatenate, string("X"), string("XB P "));
        FoldPostOrder(loctestnum, loctesterr, vec, true, &FoldStringConcatenate, string("X"), string("XP B "));

        Exists(loctestnum, loctesterr, vec, false, string("B"));

        lasd::SortableVector<string> copvec(vec);
        EqualVector(loctestnum, loctesterr, vec, copvec, true);

        MapPreOrder(loctestnum, loctesterr, vec, true, [](string & str) {
            MapStringAppend(str, string("!"));
        });

        MapPostOrder(loctestnum, loctesterr, vec, true, [](string & str) {
            MapStringAppend(str, string("!"));
        });

        NonEqualVector(loctestnum, loctesterr, vec, copvec, true);

        copvec = move(vec);
        FoldPreOrder(loctestnum, loctesterr, copvec, true, &FoldStringConcatenate, string("?"), string("?B !!P !!"));

        lasd::SortableVector<string> movvec(move(vec));
        FoldPreOrder(loctestnum, loctesterr, movvec, true, &FoldStringConcatenate, string("?"), string("?B P "));

        lasd::SortableVector<string> chk(movvec);
        movvec.Sort();
        Sort(loctestnum, loctesterr, chk, movvec, true);
        FoldPreOrder(loctestnum, loctesterr, movvec, true, &FoldStringConcatenate, string("?"), string("?B P "));
        SetAt(loctestnum, loctesterr, vec, false, 1, string(""));
        vec.Resize(1);
        SetAt(loctestnum, loctesterr, vec, true, 0, string("X"));

        movvec.Clear();
        Clear(loctestnum, loctesterr, vec);
        Empty(loctestnum, loctesterr, movvec, true);
    } catch(...) {
        loctestnum++;
        loctesterr++;
        cout << endl << "Unmanaged error! " << endl;
    }
    cout << "End of Vector<string> Test! (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << endl;
    testnum += loctestnum;
    testerr += loctesterr;
}

// Vector Test
void testVector(uint & testnum, uint & testerr) {
    uint loctestnum = 0, loctesterr = 0;
    testVectorInt(loctestnum, loctesterr);
    testVectorDouble(loctestnum, loctesterr);
    testVectorString(loctestnum, loctesterr);
    testnum += loctestnum;
    testerr += loctesterr;
    cout << endl << "Exercise - Vector (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << endl;
}
/* ************************************************************************** */

// List<int> Test
void testListInt(uint & testnum, uint & testerr) {
    uint loctestnum = 0, loctesterr = 0;
    cout << endl << "Begin of List<int> Test:" << endl;
    try {
        lasd::List<int> lst;
        lasd::List<int> lstq;
        lstq = lst;
        EqualList(loctestnum, loctesterr, lst, lstq, true);
        Size(loctestnum, loctesterr, lst, true, 0);
        Empty(loctestnum, loctesterr, lst, true);
        Size(loctestnum, loctesterr, lst, false, 4);

        GetFront(loctestnum, loctesterr, lst, false, 0);
        GetBack(loctestnum, loctesterr, lst, false, 0);

        Exists(loctestnum, loctesterr, lst, false, 0);

        TraversePostOrder(loctestnum, loctesterr, lst, true, &TraversePrint<int>);
        TraversePreOrder(loctestnum, loctesterr, lst, true, &TraversePrint<int>);
        FoldPreOrder(loctestnum, loctesterr, lst, true, &FoldAdd<int>, 0, 0);
        FoldPostOrder(loctestnum, loctesterr, lst, true, &FoldAdd<int>, 0, 0);

        RemoveFromFront(loctestnum, loctesterr, lst, false);
        FrontNRemove(loctestnum, loctesterr, lst, false, 0);

        InsertAtBack(loctestnum, loctesterr, lst, true, 5);
        InsertAtFront(loctestnum, loctesterr, lst, true, 6);
        InsertAtFront(loctestnum, loctesterr, lst, true, 7);
        InsertAtBack(loctestnum, loctesterr, lst, true, 9);
        InsertAtFront(loctestnum, loctesterr, lst, true, 2);
        Traverse(loctestnum, loctesterr, lst, true, &TraversePrint<int>);

        InsertAtFrontM(loctestnum, loctesterr, lst, true, 9);
        RemoveFromFront(loctestnum, loctesterr, lst, true);
        Traverse(loctestnum, loctesterr, lst, true, &TraversePrint<int>);

        InsertAtBackM(loctestnum, loctesterr, lst, true, 0);
        RemoveFromBack(loctestnum, loctesterr, lst, true);
        Traverse(loctestnum, loctesterr, lst, true, &TraversePrint<int>);

        GetFront(loctestnum, loctesterr, lst, true, 2);
        GetBack(loctestnum, loctesterr, lst, true, 9);
        SetFront(loctestnum, loctesterr, lst, true, 3);
        SetBack(loctestnum, loctesterr, lst, true, 6);

        Traverse(loctestnum, loctesterr, lst, true, &TraversePrint<int>);

        GetAt(loctestnum, loctesterr, lst, true, 3, 5);
        SetAt(loctestnum, loctesterr, lst, true, 3, 6);

        Exists(loctestnum, loctesterr, lst, false, 90);
        Exists(loctestnum, loctesterr, lst, true, 6);

        Traverse(loctestnum, loctesterr, lst, true, &TraversePrint<int>);
        TraversePreOrder(loctestnum, loctesterr, lst, true, &TraversePrint<int>);
        TraversePostOrder(loctestnum, loctesterr, lst, true, &TraversePrint<int>);

        Fold(loctestnum, loctesterr, lst, true, &FoldParity, 0, 0);
        FoldPreOrder(loctestnum, loctesterr, lst, true, &FoldAdd<int>, 0, 28);
        FoldPostOrder(loctestnum, loctesterr, lst, true, &FoldMultiply<int>, 1, 4536);

        RemoveFromFront(loctestnum, loctesterr, lst, true);
        FrontNRemove(loctestnum, loctesterr, lst, true, 7);
        FoldPostOrder(loctestnum, loctesterr, lst, true, &FoldMultiply<int>, 1, 216);

        lasd::List<int> coplst(lst);
        EqualList(loctestnum, loctesterr, lst, coplst, true);
        Map(loctestnum, loctesterr, lst, true, &MapDouble<int>);

        MapPreOrder(loctestnum, loctesterr, lst, true, &MapIncrement<int>);
        NonEqualList(loctestnum, loctesterr, lst, coplst, true);
        Traverse(loctestnum, loctesterr, lst, true, &TraversePrint<int>);

        InsertAtFront(loctestnum, loctesterr, lst, true, 0);
        InsertAtBack(loctestnum, loctesterr, lst, true, 0);
        NonEqualList(loctestnum, loctesterr, lst, coplst, true);
        coplst = lst;
        EqualList(loctestnum, loctesterr, lst, coplst, true);
        Traverse(loctestnum, loctesterr, coplst, true, &TraversePrint<int>);
        Traverse(loctestnum, loctesterr, lst, true, &TraversePrint<int>);

        RemoveFromFront(loctestnum, loctesterr, coplst, true);
        FrontNRemove(loctestnum, loctesterr, coplst, true, 13);
        coplst = move(lst);
        Traverse(loctestnum, loctesterr, coplst, true, &TraversePrint<int>);
        Traverse(loctestnum, loctesterr, lst, true, &TraversePrint<int>);

        FoldPreOrder(loctestnum, loctesterr, lst, true, &FoldAdd<int>, 0, 26);
        FoldPreOrder(loctestnum, loctesterr, coplst, true, &FoldAdd<int>, 0, 39);

        lasd::List<int> movlst(move(lst));
        MapPostOrder(loctestnum, loctesterr, movlst, true, &MapIncrement<int>);
        Traverse(loctestnum, loctesterr, movlst, true, &TraversePrint<int>);
        FoldPreOrder(loctestnum, loctesterr, movlst, false, &FoldAdd<int>, 0, 45);

        InsertAtFront(loctestnum, loctesterr, movlst, true, 6);
        InsertAtBack(loctestnum, loctesterr, movlst, true, 8);
        RemoveFromFront(loctestnum, loctesterr, movlst, true);
        InsertAtBack(loctestnum, loctesterr, movlst, true, 7);
        Traverse(loctestnum, loctesterr, movlst, true, &TraversePrint<int>);

        FoldPreOrder(loctestnum, loctesterr, movlst, true, &FoldAdd<int>, 1, 45);
        BackNRemove(loctestnum, loctesterr, movlst, false, 0);

        Clear(loctestnum, loctesterr, movlst);
        Empty(loctestnum, loctesterr, movlst, true);
        Size(loctestnum, loctesterr, movlst, true, 0);
    } catch(...) {
        loctestnum++;
        loctesterr++;
        cout << endl << "Unmanaged error! " << endl;
    }
    cout << "End of List<int> Test! (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << endl;
    testnum += loctestnum;
    testerr += loctesterr;
}

// List<double> Test
void testListDouble(uint & testnum, uint & testerr) {
    uint loctestnum = 0, loctesterr = 0;
    cout << endl << "Begin of List<double> Test:" << endl;
    try {
        lasd::List<double> lst;
        lasd::List<double> lstq;
        lstq = lst;

        EqualList(loctestnum, loctesterr, lst, lstq, true);
        Clear(loctestnum, loctesterr, lstq);
        Empty(loctestnum, loctesterr, lst, true);
        Size(loctestnum, loctesterr, lst, true, 0);

        GetFront(loctestnum, loctesterr, lst, false, 0.0);
        GetBack(loctestnum, loctesterr, lst, false, 0.0);
        Exists(loctestnum, loctesterr, lst, false, 0.0);

        RemoveFromFront(loctestnum, loctesterr, lst, false);
        FrontNRemove(loctestnum, loctesterr, lst, false, 0.0);

        InsertAtBack(loctestnum, loctesterr, lst, true, -1.5);
        InsertAtBack(loctestnum, loctesterr, lst, true, 1.5);
        SetFront(loctestnum, loctesterr, lst, true, -3.5);
        SetBack(loctestnum, loctesterr, lst, true, 3.5);
        Traverse(loctestnum, loctesterr, lst, true, &TraversePrint<double>);

        lst.Clear();
        InsertAtFrontM(loctestnum, loctesterr, lst, true, 4.1);
        RemoveFromFront(loctestnum, loctesterr, lst, true);
        InsertAtBackM(loctestnum, loctesterr, lst, true, 9.2);
        RemoveFromBack(loctestnum, loctesterr, lst, true);
        InsertAtBack(loctestnum, loctesterr, lst, true, 2.5);
        InsertAtFront(loctestnum, loctesterr, lst, true, 3.4);
        InsertAtFront(loctestnum, loctesterr, lst, true, 5.5);
        InsertAtBack(loctestnum, loctesterr, lst, true, 1.4);
        Traverse(loctestnum, loctesterr, lst, true, &TraversePrint<double>);

        GetAt(loctestnum, loctesterr, lst, true, 3, 1.4);
        SetAt(loctestnum, loctesterr, lst, true, 3, 0.5);
        Traverse(loctestnum, loctesterr, lst, true, &TraversePrint<double>);

        GetFront(loctestnum, loctesterr, lst, true, 5.5);
        GetBack(loctestnum, loctesterr, lst, false, 9.1);

        Exists(loctestnum, loctesterr, lst, false, 0.4);
        Exists(loctestnum, loctesterr, lst, false, -3.5);

        TraversePreOrder(loctestnum, loctesterr, lst, true, &TraversePrint<double>);
        TraversePostOrder(loctestnum, loctesterr, lst, true, &TraversePrint<double>);
        Traverse(loctestnum, loctesterr, lst, true, &TraversePrint<double>);

        Fold(loctestnum, loctesterr, lst, false, &FoldAdd<double>, 0, 0);
        Fold(loctestnum, loctesterr, lst, true, &FoldAdd<double>, 0, 10);
        FoldPreOrder(loctestnum, loctesterr, lst, true, &FoldAdd<double>, 0.0, 11.9);
        FoldPostOrder(loctestnum, loctesterr, lst, false, &FoldMultiply<double>, 1.0, 9.91);
        FoldPostOrder(loctestnum, loctesterr, lst, true, &FoldMultiply<double>, 1.0, 23.375);

        lasd::List<double> coplst(lst);
        EqualList(loctestnum, loctesterr, lst, coplst, true);
        Traverse(loctestnum, loctesterr, lst, true, &TraversePrint<double>);

        Map(loctestnum, loctesterr, lst, true, &MapHalf<double>);
        Traverse(loctestnum, loctesterr, lst, true, &TraversePrint<double>);
        NonEqualList(loctestnum, loctesterr, lst, coplst, true);
        BackNRemove(loctestnum, loctesterr, coplst, true, 0.5);
        Traverse(loctestnum, loctesterr, coplst, true, &TraversePrint<double>);
        Traverse(loctestnum, loctesterr, lst, true, &TraversePrint<double>);
        MapPostOrder(loctestnum, loctesterr, coplst, true, &MapIncrement<double>);
        lasd::List<double> movlst(move(coplst));
        MapPreOrder(loctestnum, loctesterr, movlst, true, &MapInvert<double>);

        Traverse(loctestnum, loctesterr, movlst, true, &TraversePrint<double>);
        Clear(loctestnum, loctesterr, movlst);
    } catch(...) {
        loctestnum++;
        loctesterr++;
        cout << endl << "Unmanaged error! " << endl;
    }
    cout << "End of List<double> Test! (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << endl;
    testnum += loctestnum;
    testerr += loctesterr;
}

// List<string> Test
void testListString(uint & testnum, uint & testerr) {
    uint loctestnum = 0, loctesterr = 0;
    cout << endl << "Begin of List<string> Test:" << endl;
    try {
        lasd::List<string> lst;
        lasd::List<string> lstq;
        lstq = lst;

        EqualList(loctestnum, loctesterr, lst, lstq, true);
        Clear(loctestnum, loctesterr, lstq);
        Empty(loctestnum, loctesterr, lst, true);
        Size(loctestnum, loctesterr, lst, true, 0);

        GetFront(loctestnum, loctesterr, lst, false, string("A"));
        GetBack(loctestnum, loctesterr, lst, false, string("A"));
        Exists(loctestnum, loctesterr, lst, false, string("A"));

        RemoveFromFront(loctestnum, loctesterr, lst, false);
        FrontNRemove(loctestnum, loctesterr, lst, false, string("A"));
        
        Traverse(loctestnum, loctesterr, lst, true, &TraversePrint<string>);
        TraversePreOrder(loctestnum, loctesterr, lst, true, &TraversePrint<string>);
        TraversePostOrder(loctestnum, loctesterr, lst, true, &TraversePrint<string>);

        InsertAtFront(loctestnum, loctesterr, lst, true, string("N"));
        InsertAtBack(loctestnum, loctesterr, lst, true, string("A"));
        SetFront(loctestnum, loctesterr, lst, true, string("A"));
        SetBack(loctestnum, loctesterr, lst, true, string("B"));
        Traverse(loctestnum, loctesterr, lst, true, &TraversePrint<string>);
        GetFront(loctestnum, loctesterr, lst, true, string("A"));
        GetBack(loctestnum, loctesterr, lst, true, string("B"));

        Exists(loctestnum, loctesterr, lst, true, string("B"));

        InsertAtFrontM(loctestnum, loctesterr, lst, true, string("front"));
        RemoveFromFront(loctestnum, loctesterr, lst, true);
        InsertAtBackM(loctestnum, loctesterr, lst, true,  string("back"));
        GetAt(loctestnum, loctesterr, lst, true, 2, string("back"));
        SetAt(loctestnum, loctesterr, lst, true, 2, string("B"));
        RemoveFromBack(loctestnum, loctesterr, lst, true);

        Exists(loctestnum, loctesterr, lst, false, string("front"));
        Exists(loctestnum, loctesterr, lst, false, string("back"));

        MapPreOrder(loctestnum, loctesterr, lst, true, [](string & str) {
            MapStringAppend(str, string(" "));
        });
        TraversePreOrder(loctestnum, loctesterr, lst, true, &TraversePrint<string>);
        FoldPostOrder(loctestnum, loctesterr, lst, true, &FoldStringConcatenate, string("X"), string("XB A "));
        FoldPreOrder(loctestnum, loctesterr, lst, true, &FoldStringConcatenate, string("X"), string("XA B "));

        Exists(loctestnum, loctesterr, lst, false, string("B"));

        lasd::List<string> coplst(lst);
        EqualList(loctestnum, loctesterr, lst, coplst, true);
        RemoveFromFront(loctestnum, loctesterr, coplst, true);
        NonEqualList(loctestnum, loctesterr, lst, coplst, true);

        lst = coplst;
        EqualList(loctestnum, loctesterr, lst, coplst, true);
        InsertAtBack(loctestnum, loctesterr, lst, true, string("U"));
        InsertAtFront(loctestnum, loctesterr, lst, true, string("F"));
        NonEqualList(loctestnum, loctesterr, lst, coplst, true);

        coplst = move(lst);
        FoldPreOrder(loctestnum, loctesterr, coplst, true, &FoldStringConcatenate, string("?"), string("?FB U"));
        MapPostOrder(loctestnum, loctesterr, coplst, true, [](string & str) {
            MapStringNonEmptyAppend(str, string("U"));
        });
        Map(loctestnum, loctesterr, coplst, true, [](string & str) {
            MapStringNonEmptyAppend(str, string("U"));
        });
        Traverse(loctestnum, loctesterr, coplst, true, &TraversePrint<string>);
        Clear(loctestnum, loctesterr, coplst);

    } catch(...) {
        loctestnum++;
        loctesterr++;
        cout << endl << "Unmanaged error! " << endl;
    }
    cout << "End of List<string> Test! (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << endl;
    testnum += loctestnum;
    testerr += loctesterr;
}

// List Test
void testList(uint & testnum, uint & testerr) {
    uint loctestnum = 0, loctesterr = 0;
    testListInt(loctestnum, loctesterr);
    testListDouble(loctestnum, loctesterr);
    testListString(loctestnum, loctesterr);
    testnum += loctestnum;
    testerr += loctesterr;
    cout << endl << "Exercise 1A - List (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << endl;
}

// Set<int> Test
void testSetInt(lasd::Set<int> & set, uint & testnum, uint & testerr) {
    uint loctestnum = 0, loctesterr = 0;
    try {
        Traverse(loctestnum, loctesterr, set, true, &TraversePrint<int>);

        Empty(loctestnum, loctesterr, set, false);
        Size(loctestnum, loctesterr, set, true, 7);

        GetAt(loctestnum, loctesterr, set, true, 0, 0);
        GetBack(loctestnum, loctesterr, set, false, 0);
        GetFront(loctestnum, loctesterr, set, false, 104);

        Traverse(loctestnum, loctesterr, set, true, &TraversePrint<int>);
        TraversePostOrder(loctestnum, loctesterr, set, true, &TraversePrint<int>);
        TraversePreOrder(loctestnum, loctesterr, set, true, &TraversePrint<int>);

        Min(loctestnum, loctesterr, set, true, 0);
        Min(loctestnum, loctesterr, set, false, 1);
        Max(loctestnum, loctesterr, set, true, 6);
        Max(loctestnum, loctesterr, set, false, 0);

        RemoveMin(loctestnum, loctesterr, set, true);
        MinNRemove(loctestnum, loctesterr, set, true, 1);

        InsertC(loctestnum, loctesterr, set, true, -1);
        InsertC(loctestnum, loctesterr, set, true, 1);

        Min(loctestnum, loctesterr, set, true, -1);
        MaxNRemove(loctestnum, loctesterr, set, true, 6);
        Size(loctestnum, loctesterr, set, true, 6);

        InsertC(loctestnum, loctesterr, set, true, 8);
        Size(loctestnum, loctesterr, set, true, 7);

        Max(loctestnum, loctesterr, set, true, 8);
        InsertC(loctestnum, loctesterr, set, true, 9);
        Size(loctestnum, loctesterr, set, true, 8);

        Exists(loctestnum, loctesterr, set, true, 8);
        Exists(loctestnum, loctesterr, set, false, 90);
        Exists(loctestnum, loctesterr, set, false, 0);
        Exists(loctestnum, loctesterr, set, true, -1);
        Exists(loctestnum, loctesterr, set, true, 3);
        Exists(loctestnum, loctesterr, set, true, 4);

        InsertC(loctestnum, loctesterr, set, true, 12);

        Exists(loctestnum, loctesterr, set, false, 7);
        Remove(loctestnum, loctesterr, set, true, 9);

        TraversePreOrder(loctestnum, loctesterr, set, true, &TraversePrint<int>);
        TraversePostOrder(loctestnum, loctesterr, set, true, &TraversePrint<int>);

        Remove(loctestnum, loctesterr, set, true, 12);
        Remove(loctestnum, loctesterr, set, true, 2);

        TraversePreOrder(loctestnum, loctesterr, set, true, &TraversePrint<int>);
        TraversePostOrder(loctestnum, loctesterr, set, true, &TraversePrint<int>);

        Exists(loctestnum, loctesterr, set, false, 9);
        Exists(loctestnum, loctesterr, set, false, 2);

        RemoveMax(loctestnum, loctesterr, set, true);
        Max(loctestnum, loctesterr, set, true, 5);

        TraversePreOrder(loctestnum, loctesterr, set, true, &TraversePrint<int>);

        Predecessor(loctestnum, loctesterr, set, true, 4, 3);
        Predecessor(loctestnum, loctesterr, set, true, 5, 4);

        Successor(loctestnum, loctesterr, set, true, 2, 3);
        Successor(loctestnum, loctesterr, set, true, 4, 5);

        SuccessorNRemove(loctestnum, loctesterr, set, true, 0, 1);
        Min(loctestnum, loctesterr, set, true, -1);

        TraversePreOrder(loctestnum, loctesterr, set, true, &TraversePrint<int>);

        PredecessorNRemove(loctestnum, loctesterr, set, true, 7, 5);
        TraversePreOrder(loctestnum, loctesterr, set, true, &TraversePrint<int>);

        Max(loctestnum, loctesterr, set, true, 4);

        TraversePostOrder(loctestnum, loctesterr, set, true, &TraversePrint<int>);

        Fold(loctestnum, loctesterr, set, true, &FoldAdd<int>, 0, 6);
        FoldPreOrder(loctestnum, loctesterr, set, true, &FoldAdd<int>, 0, 6);
        FoldPostOrder(loctestnum, loctesterr, set, true, &FoldAdd<int>, 0, 6);

        TraversePreOrder(loctestnum, loctesterr, set, true, &TraversePrint<int>);
        TraversePostOrder(loctestnum, loctesterr, set, true, &TraversePrint<int>);
        RemovePredecessor(loctestnum, loctesterr, set, false, -3);
        RemovePredecessor(loctestnum, loctesterr, set, true, 4);
        RemovePredecessor(loctestnum, loctesterr, set, true, 0);
        Traverse(loctestnum, loctesterr, set, true, &TraversePrint<int>);

        RemoveSuccessor(loctestnum, loctesterr, set, false, 7);
        RemoveSuccessor(loctestnum, loctesterr, set, true, 2);

        Clear(loctestnum, loctesterr, set);
        Clear(loctestnum, loctesterr, set);
        InsertM(loctestnum, loctesterr, set, true, move(1));
        InsertC(loctestnum, loctesterr, set, true, 3);
        InsertC(loctestnum, loctesterr, set, true, -1);
        InsertC(loctestnum, loctesterr, set, false, -1);

        Traverse(loctestnum, loctesterr, set, true, &TraversePrint<int>);
        lasd::List<int> list;
        InsertAllC(loctestnum, loctesterr, set, true, list);

        list.InsertAtBack(3);
        list.InsertAtFront(4);
        list.InsertAtFront(9);
        list.InsertAtFront(1);
        list.InsertAtBack(7);

        InsertAllC(loctestnum, loctesterr, set, false, list);
        lasd::List<int> list2;
        list2.InsertAtFront(15);
        list2.InsertAtFront(13);
        list2.InsertAtFront(11);

        InsertAllM(loctestnum, loctesterr, set, true, move(list2));

        Remove(loctestnum, loctesterr, set, true, -1);
        Remove(loctestnum, loctesterr, set, true, 1);
        Remove(loctestnum, loctesterr, set, false, 190);

        RemoveAll(loctestnum, loctesterr, set, false, list);
        Traverse(loctestnum, loctesterr, set, true, &TraversePrint<int>);

        list2.Clear();
        list2.InsertAtFront(3);
        list2.InsertAtFront(190);

        InsertSomeC(loctestnum, loctesterr, set, true, list2);
        list2.InsertAtFront(22);

        InsertSomeC(loctestnum, loctesterr, set, true, move(list2));
        Traverse(loctestnum, loctesterr, set, true, &TraversePrint<int>);
        list.Front() = 122;
        list.Back() = 91;

        RemoveSome(loctestnum, loctesterr, set, true, list);
        Traverse(loctestnum, loctesterr, set, true, &TraversePrint<int>);
        Clear(loctestnum, loctesterr, set);

        Empty(loctestnum, loctesterr, set, true);
        Size(loctestnum, loctesterr, set, true, 0);

    } catch(...) {
        loctestnum++;
        loctesterr++;
        cout << endl << "Unmanaged error! " << endl;
    }
    cout << "End of Set<int> Test! (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << endl;
    testnum += loctestnum;
    testerr += loctesterr;
}

// Set<int> Test
void testSetInt(uint & testnum, uint & testerr) {
    uint loctestnum = 0, loctesterr = 0;
    cout << endl << "Begin of Set<int> Test" << endl;
    try {
        lasd::Vector<int> vec(7);
        SetAt(loctestnum, loctesterr, vec, true, 0, 3);
        SetAt(loctestnum, loctesterr, vec, true, 2, 6);
        SetAt(loctestnum, loctesterr, vec, true, 1, 1);
        SetAt(loctestnum, loctesterr, vec, true, 4, 0);
        SetAt(loctestnum, loctesterr, vec, true, 3, 5);
        SetAt(loctestnum, loctesterr, vec, true, 6, 4);
        SetAt(loctestnum, loctesterr, vec, true, 5, 2);
        SetAt(loctestnum, loctesterr, vec, false, 50, 48);
        SetAt(loctestnum, loctesterr, vec, false, -10, 48);

        /* ********************************************************************** */

        cout << endl << "Begin of SetVec<int> Test:" << endl;
        lasd::SetVec<int> setvec(vec);


        testSetInt(setvec, loctestnum, loctesterr);
        cout << endl << "Begin of SetLst<int> Test:" << endl;
        lasd::SetLst<int> setlst(vec);
        testSetInt(setlst, loctestnum, loctesterr);
        cout << "\n";

        /* ***********************************************************************/

        setvec.InsertAll(vec);
        lasd::SetVec<int> setvec1(setvec);
        Traverse(loctestnum, loctesterr, setvec, true, &TraversePrint<int>);
        Traverse(loctestnum, loctesterr, setvec1, true, &TraversePrint<int>);
        EqualSetVec(loctestnum, loctesterr, setvec, setvec1, true);

        Remove(loctestnum, loctesterr, setvec1, true, 4);

        NonEqualSetVec(loctestnum, loctesterr, setvec, setvec1, true);
        Traverse(loctestnum, loctesterr, setvec, true, &TraversePrint<int>);
        Traverse(loctestnum, loctesterr, setvec1, true, &TraversePrint<int>);

        InsertC(loctestnum, loctesterr, setvec1, true, 4);
        EqualSetVec(loctestnum, loctesterr, setvec, setvec1, true);

        lasd::SetVec<int> setvec2 = setvec1;

        Traverse(loctestnum, loctesterr, setvec1, true, &TraversePrint<int>);
        Traverse(loctestnum, loctesterr, setvec2, true, &TraversePrint<int>);

        EqualSetVec(loctestnum, loctesterr, setvec1, setvec2, true);
        RemovePredecessor(loctestnum, loctesterr, setvec1, true, 9);
        EqualSetVec(loctestnum, loctesterr, setvec1, setvec2, false);

        lasd::SetVec<int> setvec3(move(setvec2));

        Empty(loctestnum, loctesterr, setvec2, true);
        Size(loctestnum, loctesterr, setvec2, true, 0);

        Empty(loctestnum, loctesterr, setvec3, false);
        Size(loctestnum, loctesterr, setvec3, true, 7);

        setvec2 = move(setvec1);

        Empty(loctestnum, loctesterr, setvec1, true);
        Size(loctestnum, loctesterr, setvec1, true, 0);

        Empty(loctestnum, loctesterr, setvec2, false);
        Size(loctestnum, loctesterr, setvec2, true, 6);

        NonEqualSetVec(loctestnum, loctesterr, setvec3, setvec2, true);

        Traverse(loctestnum, loctesterr, setvec2, true, &TraversePrint<int>);
        Traverse(loctestnum, loctesterr, setvec3, true, &TraversePrint<int>);

        InsertC(loctestnum, loctesterr, setvec2, true, 6);
        EqualSetVec(loctestnum, loctesterr, setvec3, setvec2, true);

        /* ********************************************************************** */

        setlst.InsertAll(vec);
        lasd::SetLst<int> setlst1(setlst);

        EqualSetLst(loctestnum, loctesterr, setlst, setlst1, true);

        Remove(loctestnum, loctesterr, setlst1, true, 4);
        NonEqualSetLst(loctestnum, loctesterr, setlst, setlst1, true);
        InsertC(loctestnum, loctesterr, setlst1, true, 4);
        EqualSetLst(loctestnum, loctesterr, setlst, setlst1, true);

        lasd::SetLst<int> setlst2 = setlst1;

        EqualSetLst(loctestnum, loctesterr, setlst1, setlst2, true);
        RemovePredecessor(loctestnum, loctesterr, setlst1, true, 9);
        EqualSetLst(loctestnum, loctesterr, setlst1, setlst2, false);

        lasd::SetLst<int> setlst3(move(setlst2));

        Size(loctestnum, loctesterr, setlst2, true, 0);
        Empty(loctestnum, loctesterr, setlst2, true);

        Size(loctestnum, loctesterr, setlst3, true, 7);
        Empty(loctestnum, loctesterr, setlst3, false);

        setlst2 = move(setlst1);

        Empty(loctestnum, loctesterr, setlst1, true);
        Size(loctestnum, loctesterr, setlst1, true, 0);

        Empty(loctestnum, loctesterr, setlst2, false);
        Size(loctestnum, loctesterr, setlst2, true, 6);

        NonEqualSetLst(loctestnum, loctesterr, setlst3, setlst2, true);

        Traverse(loctestnum, loctesterr, setlst2, true, &TraversePrint<int>);
        Traverse(loctestnum, loctesterr, setlst3, true, &TraversePrint<int>);

        InsertC(loctestnum, loctesterr, setlst2, true, 6);
        EqualSetLst(loctestnum, loctesterr, setlst3, setlst2, true);
        EqualLinear(loctestnum, loctesterr, setvec3, setlst2, true);
        NonEqualLinear(loctestnum, loctesterr, setlst3, setvec2, false);

    } catch(...) {
        loctestnum++;
        loctesterr++;
        cout << endl << "Unmanaged error! " << endl;
    }
    cout << "End of Set<int> Test! (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << endl;
    testnum += loctestnum;
    testerr += loctesterr;
}

// Set<double> Test
void testSetFloat(lasd::Set<double> & set, uint & testnum, uint & testerr) {
    uint loctestnum = 0, loctesterr = 0;
    try {
        cout << endl << "Begin of Set<Float> Test" << endl << endl;

        Empty(loctestnum, loctesterr, set, false);
        Traverse(loctestnum, loctesterr, set, true, &TraversePrint<double>);
        Size(loctestnum, loctesterr, set, false, 1);
        Size(loctestnum, loctesterr, set, true, 6);

        GetAt(loctestnum, loctesterr, set, true, 3, 5.0);
        GetBack(loctestnum, loctesterr, set, false, 5.4);
        GetBack(loctestnum, loctesterr, set, true, 9.3);
        GetFront(loctestnum, loctesterr, set, true, 0.5);

        Traverse(loctestnum, loctesterr, set, true, &TraversePrint<double>);
        TraversePreOrder(loctestnum, loctesterr, set, true, &TraversePrint<double>);
        TraversePostOrder(loctestnum, loctesterr, set, true, &TraversePrint<double>);

        Min(loctestnum, loctesterr, set, true, 0.5);
        Max(loctestnum, loctesterr, set, false, 6.1);

        RemoveMin(loctestnum, loctesterr, set, true);
        MinNRemove(loctestnum, loctesterr, set, true, 0.9);

        InsertC(loctestnum, loctesterr, set, true, -1.1);
        InsertC(loctestnum, loctesterr, set, true, 1.0);

        Min(loctestnum, loctesterr, set, true, -1.1);
        MaxNRemove(loctestnum, loctesterr, set, false, 8.4);
        Size(loctestnum, loctesterr, set, true, 5);

        InsertC(loctestnum, loctesterr, set, true, 91.0);
        Size(loctestnum, loctesterr, set, false, 90);

        Max(loctestnum, loctesterr, set, true, 91.0);
        InsertC(loctestnum, loctesterr, set, true, 8.4);

        Size(loctestnum, loctesterr, set, true, 7);

        Exists(loctestnum, loctesterr, set, true, 91.0);
        Exists(loctestnum, loctesterr, set, false, 9.0);
        Exists(loctestnum, loctesterr, set, false, 0.0);
        Exists(loctestnum, loctesterr, set, true, -1.1);
        Exists(loctestnum, loctesterr, set, false, 121.0);

        TraversePreOrder(loctestnum, loctesterr, set, true, &TraversePrint<double>);
        TraversePostOrder(loctestnum, loctesterr, set, true, &TraversePrint<double>);

        Remove(loctestnum, loctesterr, set, true, 91.0);
        Remove(loctestnum, loctesterr, set, false, -11.105);

        TraversePreOrder(loctestnum, loctesterr, set, true, &TraversePrint<double>);
        TraversePostOrder(loctestnum, loctesterr, set, true, &TraversePrint<double>);

        Exists(loctestnum, loctesterr, set, false, 91.0);
        Exists(loctestnum, loctesterr, set, true, 8.4);

        TraversePreOrder(loctestnum, loctesterr, set, true, &TraversePrint<double>);
        RemoveMax(loctestnum, loctesterr, set, true);
        Max(loctestnum, loctesterr, set, true, 8.4);

        TraversePreOrder(loctestnum, loctesterr, set, true, &TraversePrint<double>);

        Predecessor(loctestnum, loctesterr, set, true, 4.0, 1.2);
        Predecessor(loctestnum, loctesterr, set, true, 4.9, 1.2);

        Successor(loctestnum, loctesterr, set, true, 1.6, 5.0);
        Successor(loctestnum, loctesterr, set, true, 4.0, 5.0);
        Successor(loctestnum, loctesterr, set, false, 4.0, 9.1);

        SuccessorNRemove(loctestnum, loctesterr, set, true, 0.0, 1.0);
        Min(loctestnum, loctesterr, set, true, -1.1);

        TraversePreOrder(loctestnum, loctesterr, set, true, &TraversePrint<double>);

        PredecessorNRemove(loctestnum, loctesterr, set, true, 7.0, 5.0);
        Max(loctestnum, loctesterr, set, true, 8.4);

        TraversePostOrder(loctestnum, loctesterr, set, true, &TraversePrint<double>);

        Fold(loctestnum, loctesterr, set, true, &FoldAdd<double>, 0.0, 8.5);
        FoldPostOrder(loctestnum, loctesterr, set, true, &FoldAdd<double>, 0.0, 8.5);
        FoldPreOrder(loctestnum, loctesterr, set, false, &FoldAdd<double>, 0.0, 9955.9);

        TraversePreOrder(loctestnum, loctesterr, set, true, &TraversePrint<double>);
        TraversePostOrder(loctestnum, loctesterr, set, true, &TraversePrint<double>);
        RemovePredecessor(loctestnum, loctesterr, set, false, -3.0);
        Traverse(loctestnum, loctesterr, set, true, &TraversePrint<double>);
        RemovePredecessor(loctestnum, loctesterr, set, true, 4.0);
        Traverse(loctestnum, loctesterr, set, true, &TraversePrint<double>);
        RemovePredecessor(loctestnum, loctesterr, set, false, -1.1);
        Traverse(loctestnum, loctesterr, set, true, &TraversePrint<double>);

        RemoveSuccessor(loctestnum, loctesterr, set, false, 700.0);
        RemoveSuccessor(loctestnum, loctesterr, set, false, 4000.1);

        Clear(loctestnum, loctesterr, set);
        Clear(loctestnum, loctesterr, set);
        InsertM(loctestnum, loctesterr, set, true, move(1.0));
        InsertC(loctestnum, loctesterr, set, true, 3.0);
        InsertC(loctestnum, loctesterr, set, true, -1.0);
        InsertC(loctestnum, loctesterr, set, false, -1.0);

        Traverse(loctestnum, loctesterr, set, true, &TraversePrint<double>);
        lasd::List<double> list;
        InsertAllC(loctestnum, loctesterr, set, true, list);

        list.InsertAtBack(4.0);
        list.InsertAtFront(5.0);
        list.InsertAtFront(9.0);
        list.InsertAtFront(1.0);
        list.InsertAtBack(2.0);

        InsertAllC(loctestnum, loctesterr, set, false, list);
        lasd::List<double> list2;
        list2.InsertAtFront(12.0);
        list2.InsertAtFront(13.0);
        list2.InsertAtFront(14.0);

        InsertAllM(loctestnum, loctesterr, set, true, move(list2));

        Remove(loctestnum, loctesterr, set, true, -1.0);
        Remove(loctestnum, loctesterr, set, true, 1.0);
        Remove(loctestnum, loctesterr, set, false, 120.0);

        RemoveAll(loctestnum, loctesterr, set, false, list);
        Traverse(loctestnum, loctesterr, set, true, &TraversePrint<double>);

        list2.Clear();
        list2.InsertAtFront(3.0);
        list2.InsertAtFront(120.0);

        InsertSomeC(loctestnum, loctesterr, set, true, list2);
        list2.InsertAtFront(121.0);

        InsertSomeC(loctestnum, loctesterr, set, true, move(list2));
        Traverse(loctestnum, loctesterr, set, true, &TraversePrint<double>);
        list.Front() = 12.0;
        list.Back() = 121.0;

        RemoveSome(loctestnum, loctesterr, set, true, list);
        Traverse(loctestnum, loctesterr, set, true, &TraversePrint<double>);
        Clear(loctestnum, loctesterr, set);

        Empty(loctestnum, loctesterr, set, true);
        Size(loctestnum, loctesterr, set, true, 0);

    } catch(...) {
        loctestnum++;
        loctesterr++;
        cout << endl << "Unmanaged error! " << endl;
    }
    cout << "End of Set<double> Test! (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << endl;
    testnum += loctestnum;
    testerr += loctesterr;
}

// Set<double> Test
void testSetFloat(uint & testnum, uint & testerr) {
    uint loctestnum = 0, loctesterr = 0;
    cout << endl << endl << "Begin of Set<double> Test" << endl;
    try {

        lasd::List<double> lst;
        InsertAtFront(loctestnum, loctesterr, lst, true, 5.0);
        InsertAtBack(loctestnum, loctesterr, lst, true, 0.9);
        InsertAtFront(loctestnum, loctesterr, lst, true, 1.2);
        InsertAtBack(loctestnum, loctesterr, lst, true, 9.1);
        InsertAtFront(loctestnum, loctesterr, lst, true, 0.5);
        InsertAtBack(loctestnum, loctesterr, lst, true, 9.3);

        TraversePreOrder(loctestnum, loctesterr, lst, true, &TraversePrint<double>);

        /* ***********************************************************************/

        lasd::SetVec<double> setvec1(lst);
        cout << endl << "Begin of SetVec<double> Test:" << endl;

        testSetFloat(setvec1, loctestnum, loctesterr);
        InsertAllC(loctestnum, loctesterr, setvec1, true, lst);
        Size(loctestnum, loctesterr, setvec1, true, 6);
        Empty(loctestnum, loctesterr, setvec1, false);

        TraversePostOrder(loctestnum, loctesterr, setvec1, true, &TraversePrint<double>);
        TraversePreOrder(loctestnum, loctesterr, setvec1, true, &TraversePrint<double>);

        lasd::SetVec<double> setvec2;

        InsertC(loctestnum, loctesterr, setvec2, true, 1.1);
        InsertC(loctestnum, loctesterr, setvec2, true, 7.4);
        InsertC(loctestnum, loctesterr, setvec2, true, 1.9);
        InsertC(loctestnum, loctesterr, setvec2, true, 3.8);
        InsertC(loctestnum, loctesterr, setvec2, true, 5.0);
        InsertC(loctestnum, loctesterr, setvec2, true, 9.0);
    
        TraversePreOrder(loctestnum, loctesterr, setvec1, true, &TraversePrint<double>);
        TraversePreOrder(loctestnum, loctesterr, setvec2, true, &TraversePrint<double>);

        EqualSetVec(loctestnum, loctesterr, setvec1, setvec2, false);
        NonEqualSetVec(loctestnum, loctesterr, setvec1, setvec2, true);

        setvec1.Clear();
        setvec2.Clear();

        InsertC(loctestnum, loctesterr, setvec1, true, 0.2);
        InsertC(loctestnum, loctesterr, setvec1, true, 1.1);
        InsertC(loctestnum, loctesterr, setvec1, true, 2.1);

        InsertC(loctestnum, loctesterr, setvec2, true, 2.1);
        InsertC(loctestnum, loctesterr, setvec2, true, 1.1);
        InsertC(loctestnum, loctesterr, setvec2, true, 0.2);


        TraversePreOrder(loctestnum, loctesterr, setvec1, true, &TraversePrint<double>);
        TraversePreOrder(loctestnum, loctesterr, setvec2, true, &TraversePrint<double>);

        EqualSetVec(loctestnum, loctesterr, setvec1, setvec2, true);
        NonEqualSetVec(loctestnum, loctesterr, setvec1, setvec2, false);

        /* ********************************************************************** */

        lasd::SetLst<double> setlst1(lst);
        cout << endl << "Begin of SetList<double> Test:" << endl;

        testSetFloat(setlst1, loctestnum, loctesterr);
        InsertAllC(loctestnum, loctesterr, setlst1, true, lst);
        Empty(loctestnum, loctesterr, setlst1, false);
        Size(loctestnum, loctesterr, setlst1, true, 6);

        TraversePreOrder(loctestnum, loctesterr, setlst1, true, &TraversePrint<double>);
        TraversePostOrder(loctestnum, loctesterr, setlst1, true, &TraversePrint<double>);

        lasd::SetLst<double> setlst2;

        InsertC(loctestnum, loctesterr, setlst2, true, 2.1);
        InsertC(loctestnum, loctesterr, setlst2, true, 0.4);
        InsertC(loctestnum, loctesterr, setlst2, true, 1.2);
        InsertC(loctestnum, loctesterr, setlst2, true, 3.5);
        InsertC(loctestnum, loctesterr, setlst2, true, 5.3);
        InsertC(loctestnum, loctesterr, setlst2, true, 4.0);

        TraversePreOrder(loctestnum, loctesterr, setvec1, true, &TraversePrint<double>);
        TraversePreOrder(loctestnum, loctesterr, setvec2, true, &TraversePrint<double>);

        EqualSetLst(loctestnum, loctesterr, setlst1, setlst2, false);
        NonEqualSetLst(loctestnum, loctesterr, setlst1, setlst2, true);

        setlst1.Clear();
        setlst2.Clear();

        InsertC(loctestnum, loctesterr, setlst1, true, 0.1);
        InsertC(loctestnum, loctesterr, setlst1, true, 5.1);
        InsertC(loctestnum, loctesterr, setlst1, true, 12.7);

        InsertC(loctestnum, loctesterr, setlst2, true, 12.7);
        InsertC(loctestnum, loctesterr, setlst2, true, 5.1);
        InsertC(loctestnum, loctesterr, setlst2, true, 0.1);

        EqualSetLst(loctestnum, loctesterr, setlst1, setlst2, true);
        NonEqualSetLst(loctestnum, loctesterr, setlst1, setlst2, false);

        EqualLinear(loctestnum, loctesterr, setvec1, setlst2, false);
        NonEqualLinear(loctestnum, loctesterr, setlst2, setvec2, true);
    } catch(...) {
        loctestnum++;
        loctesterr++;
        cout << endl << "Unmanaged error! " << endl;
    }
    cout << "End of Set<double> Test! (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << endl;
    testnum += loctestnum;
    testerr += loctesterr;
}

// Set<string> Test
void testSetString(lasd::Set<string> & set, uint & testnum, uint & testerr) {
    uint loctestnum = 0, loctesterr = 0;
    try {

        Traverse(loctestnum, loctesterr, set, true, &TraversePrint<string>);

        Empty(loctestnum, loctesterr, set, false);
        Size(loctestnum, loctesterr, set, true, 5);

        GetAt(loctestnum, loctesterr, set, true,  0, string("A"));
        GetBack(loctestnum, loctesterr, set, false, string("B"));
        GetFront(loctestnum, loctesterr, set, false, string("N"));

        Traverse(loctestnum, loctesterr, set, true, &TraversePrint<string>);
        TraversePreOrder(loctestnum, loctesterr, set, true, &TraversePrint<string>);
        TraversePostOrder(loctestnum, loctesterr, set, true, &TraversePrint<string>);

        Min(loctestnum, loctesterr, set, true,  string("A"));
        Max(loctestnum, loctesterr, set, true,  string("E"));

        RemoveMin(loctestnum, loctesterr, set, true);
        MinNRemove(loctestnum, loctesterr, set, true,  string("B"));

        InsertC(loctestnum, loctesterr, set, true,  string("B"));
        InsertC(loctestnum, loctesterr, set, true,  string("A"));

        Min(loctestnum, loctesterr, set, true,  string("A"));
        MaxNRemove(loctestnum, loctesterr, set, true, string("E"));
        Size(loctestnum, loctesterr, set, true,  4);

        InsertC(loctestnum, loctesterr, set, true,  string("Z"));
        Size(loctestnum, loctesterr, set, true,  5);
        Max(loctestnum, loctesterr, set, true,  string("Z"));

        InsertC(loctestnum, loctesterr, set, true,  string("Q"));
        Size(loctestnum, loctesterr, set, true,  6);

        Exists(loctestnum, loctesterr, set, true,  string("Z"));
        Exists(loctestnum, loctesterr, set, true,  string("A"));
        Exists(loctestnum, loctesterr, set, false, string("N"));
        Exists(loctestnum, loctesterr, set, false, string("J"));
        Exists(loctestnum, loctesterr, set, false, string("S"));
        Exists(loctestnum, loctesterr, set, true,  string("Q"));

        TraversePreOrder(loctestnum, loctesterr, set, true, &TraversePrint<string>);
        TraversePostOrder(loctestnum, loctesterr, set, true, &TraversePrint<string>);

        Remove(loctestnum, loctesterr, set, false, string("H"));
        Remove(loctestnum, loctesterr, set, true,  string("D"));

        TraversePreOrder(loctestnum, loctesterr, set, true, &TraversePrint<string>);
        TraversePostOrder(loctestnum, loctesterr, set, true, &TraversePrint<string>);

        Exists(loctestnum, loctesterr, set, false, string("a"));
        Exists(loctestnum, loctesterr, set, true, string("A"));
        Exists(loctestnum, loctesterr, set, false, string("D"));

        RemoveMax(loctestnum, loctesterr, set, true);
        Max(loctestnum, loctesterr, set, true, string("Q"));

        TraversePreOrder(loctestnum, loctesterr, set, true, &TraversePrint<string>);

        Predecessor(loctestnum, loctesterr, set, true, string("C"), string("B"));
        Predecessor(loctestnum, loctesterr, set, false, string("A"), string("B"));

        Successor(loctestnum, loctesterr, set, true, string("C"), string("Q"));
        Successor(loctestnum, loctesterr, set, false,  string("Q"), string("B"));

        SuccessorNRemove(loctestnum, loctesterr, set, true, string("C"), string("Q"));
        Min(loctestnum, loctesterr, set, true, string("A"));

        TraversePreOrder(loctestnum, loctesterr, set, true, &TraversePrint<string>);
        PredecessorNRemove(loctestnum, loctesterr, set, true, string("Z"), string("C"));
        Max(loctestnum, loctesterr, set, true, string("B"));

        TraversePostOrder(loctestnum, loctesterr, set, true, &TraversePrint<string>);
        FoldPreOrder(loctestnum, loctesterr, set, true, &FoldStringConcatenate, string("?"), string("?AB"));
        FoldPostOrder(loctestnum, loctesterr, set, true, &FoldStringConcatenate, string("?"), string("?BA"));

        TraversePreOrder(loctestnum, loctesterr, set, true, &TraversePrint<string>);
        TraversePostOrder(loctestnum, loctesterr, set, true, &TraversePrint<string>);

        InsertM(loctestnum, loctesterr, set, true, move(string("Z")));
        InsertC(loctestnum, loctesterr, set, true, string("M"));
        InsertC(loctestnum, loctesterr, set, true, string("N"));
        InsertC(loctestnum, loctesterr, set, false, string("M"));

        RemovePredecessor(loctestnum, loctesterr, set, false, string("A"));
        RemovePredecessor(loctestnum, loctesterr, set, true, string("Z"));
        RemovePredecessor(loctestnum, loctesterr, set, true, string("M"));
        Traverse(loctestnum, loctesterr, set, true, &TraversePrint<string>);

        RemoveSuccessor(loctestnum, loctesterr, set, false, string("Z"));
        RemoveSuccessor(loctestnum, loctesterr, set, true, string("C"));

        Clear(loctestnum, loctesterr, set);
        Clear(loctestnum, loctesterr, set);

        InsertM(loctestnum, loctesterr, set, true, move(string("A")));
        InsertC(loctestnum, loctesterr, set, true, string("B"));
        InsertC(loctestnum, loctesterr, set, true, string("C"));
        InsertC(loctestnum, loctesterr, set, false, string("C"));

        Traverse(loctestnum, loctesterr, set, true, &TraversePrint<string>);
        lasd::List<string> list;
        InsertAllC(loctestnum, loctesterr, set, true, list);

        list.InsertAtBack(string("C"));
        list.InsertAtFront(string("X"));
        list.InsertAtFront(string("V"));
        list.InsertAtFront(string("N"));
        list.InsertAtBack(string("L"));

        InsertAllC(loctestnum, loctesterr, set, false, list);
        lasd::List<string> list2;
        list2.InsertAtFront(string("J"));
        list2.InsertAtFront(string("P"));
        list2.InsertAtFront(string("O"));

        InsertAllM(loctestnum, loctesterr, set, true, move(list2));
        Traverse(loctestnum, loctesterr, set, true, &TraversePrint<string>);

        Remove(loctestnum, loctesterr, set, true, string("P"));
        Remove(loctestnum, loctesterr, set, true, string("L"));
        Remove(loctestnum, loctesterr, set, false, string("K"));

        RemoveAll(loctestnum, loctesterr, set, false, list);
        Traverse(loctestnum, loctesterr, set, true, &TraversePrint<string>);

        list2.Clear();
        list2.InsertAtFront(string("M"));
        list2.InsertAtFront(string("P"));

        InsertSomeC(loctestnum, loctesterr, set, true, list2);
        list2.InsertAtFront(string("D"));

        InsertSomeC(loctestnum, loctesterr, set, true, move(list2));
        Traverse(loctestnum, loctesterr, set, true, &TraversePrint<string>);
        list.Front() = string("D");
        list.Back() = string("T");

        RemoveSome(loctestnum, loctesterr, set, true, list);
        Traverse(loctestnum, loctesterr, set, true, &TraversePrint<string>);
        Clear(loctestnum, loctesterr, set);

        Empty(loctestnum, loctesterr, set, true);
        Size(loctestnum, loctesterr, set, true, 0);


    } catch(...) {
        loctestnum++;
        loctesterr++;
        cout << endl << "Unmanaged error! " << endl;
    }
    cout << "End of Set<string> Test! (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << endl;
    testnum += loctestnum;
    testerr += loctesterr;
}

// Set<string> Test
void testSetString(uint & testnum, uint & testerr) {
    uint loctestnum = 0, loctesterr = 0;
    cout << endl << "Begin of Set<string> Test" << endl;
    try {
        lasd::Vector<string> vec(5);
        SetAt(loctestnum, loctesterr, vec, true, 0, string("A"));
        SetAt(loctestnum, loctesterr, vec, true, 1, string("B"));
        SetAt(loctestnum, loctesterr, vec, true, 2, string("C"));
        SetAt(loctestnum, loctesterr, vec, true, 3, string("D"));
        SetAt(loctestnum, loctesterr, vec, true, 4, string("E"));

        cout << endl << "Begin of SetVec<string> Test:" << endl;
        lasd::SetVec<string> setvec(vec);
        testSetString(setvec, loctestnum, loctesterr);
        cout << endl << "Begin of SetLst<string> Test:" << endl;
        lasd::SetLst<string> setlst(vec);
        testSetString(setlst, loctestnum, loctesterr);
        cout << "\n";

        /* ********************************************************************** */

        EqualLinear(loctestnum, loctesterr, setvec, setlst, true);

    } catch(...) {
        loctestnum++;
        loctesterr++;
        cout << endl << "Unmanaged error! " << endl;
    }
    cout << "End of Set<string> Test! (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << endl;
    testnum += loctestnum;
    testerr += loctesterr;
}


/* ***************************************************************** */
// - - - - - -   - - - - - -  TEMPLATE 2 - - - - - -   - - - - - -  //
/* ******************************************************************/


void testHeapInt(uint & testnum, uint & testerr) {
    uint loctestnum = 0, loctesterr = 0;
    cout << endl << "Begin of Heap<int> Test:" << endl;
    try {

        lasd::HeapVec<int> heapEmpty;
        lasd::HeapVec<int> heapEmpty2;
        heapEmpty2 = heapEmpty;
        Traverse(loctestnum, loctesterr, heapEmpty, true, &TraversePrint<int>);
        TraversePreOrder(loctestnum, loctesterr, heapEmpty, true, &TraversePrint<int>);
        TraversePostOrder(loctestnum, loctesterr, heapEmpty, true, &TraversePrint<int>);

        IsHeap(loctestnum, loctesterr, heapEmpty, true);

        Size(loctestnum, loctesterr, heapEmpty, true, 0);
        Size(loctestnum, loctesterr, heapEmpty, false, 10);
        Empty(loctestnum, loctesterr, heapEmpty, true);
        Clear(loctestnum, loctesterr, heapEmpty);

        Fold(loctestnum, loctesterr, heapEmpty, true, &FoldAdd<int>, 0, 0);
        FoldPreOrder(loctestnum, loctesterr, heapEmpty, true, &FoldAdd<int>, 0, 0);
        FoldPostOrder(loctestnum, loctesterr, heapEmpty, true, &FoldAdd<int>, 0, 0);

        Map(loctestnum, loctesterr, heapEmpty, true, &MapParityInvert<int>);
        MapPostOrder(loctestnum, loctesterr, heapEmpty, true, &MapParityInvert<int>);
        MapPreOrder(loctestnum, loctesterr, heapEmpty, true, &MapParityInvert<int>);

        GetBack(loctestnum, loctesterr, heapEmpty, false, 2);
        GetFront(loctestnum, loctesterr, heapEmpty, false, 2);
        GetAt(loctestnum, loctesterr, heapEmpty, false, 2, 0);
        GetAt(loctestnum, loctesterr, heapEmpty, false, 0, 0);

        SetAt(loctestnum, loctesterr, heapEmpty, false, 2, 1);
        SetBack(loctestnum, loctesterr, heapEmpty, false, 2);
        SetFront(loctestnum, loctesterr, heapEmpty, false, 3);

        Exists(loctestnum, loctesterr, heapEmpty, false, 2);
        EqualLinear(loctestnum, loctesterr, heapEmpty, heapEmpty2, true);
        heapEmpty.Heapify();
        heapEmpty.Sort();


        lasd::Vector<int> vec(12);
        SetAt(loctestnum, loctesterr, vec, true, 0, 5);
        SetAt(loctestnum, loctesterr, vec, true, 1, 2);
        SetAt(loctestnum, loctesterr, vec, true, 2, 1);
        SetAt(loctestnum, loctesterr, vec, true, 3, 3);
        SetAt(loctestnum, loctesterr, vec, true, 4, 20);
        SetAt(loctestnum, loctesterr, vec, true, 5, 15);
        SetAt(loctestnum, loctesterr, vec, true, 6, 0);
        SetAt(loctestnum, loctesterr, vec, true, 7, 8);
        SetAt(loctestnum, loctesterr, vec, true, 8, 11);
        SetAt(loctestnum, loctesterr, vec, true, 9, 22);
        SetAt(loctestnum, loctesterr, vec, true, 10, 77);
        SetAt(loctestnum, loctesterr, vec, true, 11, 39);


        lasd::HeapVec<int> heap1(std::move(vec));
        EqualLinear(loctestnum, loctesterr, heap1, heapEmpty, false);
       
        Traverse(loctestnum, loctesterr, heap1, true, &TraversePrint<int>);

        SetAt(loctestnum, loctesterr, heap1, true, 1, 10);
        SetBack(loctestnum, loctesterr, heap1, true, 0);
        SetFront(loctestnum, loctesterr, heap1, true, 11);

        GetBack(loctestnum, loctesterr, heap1, true, 0);
        GetFront(loctestnum, loctesterr, heap1, true, 11);
        GetAt(loctestnum, loctesterr, heap1, true, 4, 20);
        GetAt(loctestnum, loctesterr, heap1, true, 5, 15);
        heap1.Heapify();


        Traverse(loctestnum, loctesterr, heap1, true, &TraversePrint<int>);
        TraversePreOrder(loctestnum, loctesterr, heap1, true, &TraversePrint<int>);
        TraversePostOrder(loctestnum, loctesterr, heap1, true, &TraversePrint<int>);


        IsHeap(loctestnum, loctesterr, heap1, true);

        SetAt(loctestnum, loctesterr, vec, true, 0, 2);
        SetAt(loctestnum, loctesterr, vec, true, 1, 5);
        SetAt(loctestnum, loctesterr, vec, true, 2, 1);
        SetAt(loctestnum, loctesterr, vec, true, 3, 3);
        SetAt(loctestnum, loctesterr, vec, true, 4, 20);
        SetAt(loctestnum, loctesterr, vec, true, 5, 0);
        SetAt(loctestnum, loctesterr, vec, true, 6, 15);
        SetAt(loctestnum, loctesterr, vec, true, 7, 8);
        SetAt(loctestnum, loctesterr, vec, true, 8, 22);
        SetAt(loctestnum, loctesterr, vec, true, 9, 11);
        SetAt(loctestnum, loctesterr, vec, true, 10, 39);
        SetAt(loctestnum, loctesterr, vec, true, 11, 77);

        lasd::HeapVec<int> heap2(vec);

        IsHeap(loctestnum, loctesterr, heap2, true);
        Traverse(loctestnum, loctesterr, heap2, true, &TraversePrint<int>);

        EqualLinear(loctestnum, loctesterr, heap1, heap2, false);

        heap1.Sort();

        IsHeap(loctestnum, loctesterr, heap1, false);
        Traverse(loctestnum, loctesterr, heap1, true, &TraversePrint<int>);

        EqualLinear(loctestnum, loctesterr, heap1, heap2, false);

        lasd::HeapVec<int> heap3(heap2);

        EqualLinear(loctestnum, loctesterr, heap2, heap3, true);

        Empty(loctestnum, loctesterr, heap3, false);
        Size(loctestnum, loctesterr, heap3, true, 12);
        Size(loctestnum, loctesterr, heap3, false, 1);

        lasd::HeapVec<int> heap4(std::move(heap3));

        EqualLinear(loctestnum, loctesterr, heap2, heap3, false);
        EqualLinear(loctestnum, loctesterr, heap2, heap4, true);

        Empty(loctestnum, loctesterr, heap3, true);
        Size(loctestnum, loctesterr, heap3, true, 0);

        Empty(loctestnum, loctesterr, heap4, false);
        Size(loctestnum, loctesterr, heap4, true, 12);

        heap2.Sort();

        EqualLinear(loctestnum, loctesterr, heap2, heap4, false);

        heap3 = heap4;

        EqualLinear(loctestnum, loctesterr, heap2, heap3, false);
        EqualLinear(loctestnum, loctesterr, heap3, heap4, true);

        heap3 = std::move(heap2);

        EqualLinear(loctestnum, loctesterr, heap2, heap3, false);
        EqualLinear(loctestnum, loctesterr, heap2, heap4, true);
        EqualLinear(loctestnum, loctesterr, heap3, heap4, false);

        TraversePreOrder(loctestnum, loctesterr, heap2, true, &TraversePrint<int>);
        TraversePostOrder(loctestnum, loctesterr, heap2, true, &TraversePrint<int>);

        FoldPreOrder(loctestnum, loctesterr, heap2, true, &FoldAdd<int>, 0, 203);
        FoldPostOrder(loctestnum, loctesterr, heap2, true, &FoldAdd<int>, 0, 203);

        MapPreOrder(loctestnum, loctesterr, heap2, true, &MapInvert<int>);
        TraversePreOrder(loctestnum, loctesterr, heap2, true, &TraversePrint<int>);

        IsHeap(loctestnum, loctesterr, heap2, false);

        FoldPreOrder(loctestnum, loctesterr, heap2, true, &FoldAdd<int>, 0, -203);
        FoldPostOrder(loctestnum, loctesterr, heap2, true, &FoldAdd<int>, 0, -203);

        MapPostOrder(loctestnum, loctesterr, heap2, true, &MapInvert<int>);
        TraversePreOrder(loctestnum, loctesterr, heap2, true, &TraversePrint<int>);

        MapPostOrder(loctestnum, loctesterr, heap2, true, &MapParityInvert<int>);
        TraversePreOrder(loctestnum, loctesterr, heap2, true, &TraversePrint<int>);

        heap2.Heapify();

        TraversePreOrder(loctestnum, loctesterr, heap2, true, &TraversePrint<int>);

        FoldPreOrder(loctestnum, loctesterr, heap2, true, &FoldAdd<int>, 0, -99);
        FoldPostOrder(loctestnum, loctesterr, heap2, true, &FoldAdd<int>, 0, -99);

        MapPreOrder(loctestnum, loctesterr, heap2, true, &MapParityInvert<int>);
        TraversePreOrder(loctestnum, loctesterr, heap2, true, &TraversePrint<int>);

        heap2.Heapify();

        TraversePreOrder(loctestnum, loctesterr, heap2, true, &TraversePrint<int>);

        EqualLinear(loctestnum, loctesterr, heap1, heap2, false);

        heap2.Sort();

        IsHeap(loctestnum, loctesterr, heap3, false);

        heap3.Heapify();

        IsHeap(loctestnum, loctesterr, heap3, true);

        heap3.Sort();
        TraversePreOrder(loctestnum, loctesterr, heap3, true, &TraversePrint<int>);
        cout << heap3[1] << endl;
        heap3[1] = 2;
        TraversePreOrder(loctestnum, loctesterr, heap3, true, &TraversePrint<int>);

        IsHeap(loctestnum, loctesterr, heap3, false);

    } catch(...) {
        loctestnum++;
        loctesterr++;
        cout << endl << "Unmanaged error! " << endl;
    }
    cout << "End of Heap<int> Test! (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << endl;
    testnum += loctestnum;
    testerr += loctesterr;
}

void testHeapDouble(uint & testnum, uint & testerr) {
    uint loctestnum = 0, loctesterr = 0;
    cout << endl << "Begin of Heap<double> Test:" << endl;
    try {

        lasd::Vector<double> vec(14);
        SetAt(loctestnum, loctesterr, vec, true, 0, 1.5);
        SetAt(loctestnum, loctesterr, vec, true, 1, 3.02);
        SetAt(loctestnum, loctesterr, vec, true, 2, 1.125);
        SetAt(loctestnum, loctesterr, vec, true, 3, 0.0);
        SetAt(loctestnum, loctesterr, vec, true, 4, 9.25);
        SetAt(loctestnum, loctesterr, vec, true, 5, 5.5);
        SetAt(loctestnum, loctesterr, vec, true, 6, 0.0);
        SetAt(loctestnum, loctesterr, vec, true, 7, 8.25);
        SetAt(loctestnum, loctesterr, vec, true, 8, 11.5);
        SetAt(loctestnum, loctesterr, vec, true, 9, 26.5);
        SetAt(loctestnum, loctesterr, vec, true, 10, 71.95);
        SetAt(loctestnum, loctesterr, vec, true, 11, 3.125);
        SetAt(loctestnum, loctesterr, vec, true, 12, 10.5);
        SetAt(loctestnum, loctesterr, vec, true, 13, 67.65);

        lasd::HeapVec<double> heap(vec);

        TraversePreOrder(loctestnum, loctesterr, heap, true, &TraversePrint<double>);
        TraversePostOrder(loctestnum, loctesterr, heap, true, &TraversePrint<double>);

        SetAt(loctestnum, loctesterr, heap, true, 1, 10.5);
        SetBack(loctestnum, loctesterr, heap, true, 0.0);
        SetFront(loctestnum, loctesterr, heap, true, 11.5);

        GetBack(loctestnum, loctesterr, heap, true, 0.0);
        GetFront(loctestnum, loctesterr, heap, true, 11.5);
        GetAt(loctestnum, loctesterr, heap, true, 5, 10.5);
        GetAt(loctestnum, loctesterr, heap, true, 12, 5.5);
        GetAt(loctestnum, loctesterr, heap, true, 1, 10.5);
        heap.Sort();

        IsHeap(loctestnum, loctesterr, heap, false);
        TraversePreOrder(loctestnum, loctesterr, heap, true, &TraversePrint<double>);
        TraversePostOrder(loctestnum, loctesterr, heap, true, &TraversePrint<double>);

        heap.Heapify();

        TraversePreOrder(loctestnum, loctesterr, heap, true, &TraversePrint<double>);
        TraversePreOrder(loctestnum, loctesterr, heap, true, &TraversePrint<double>);
        IsHeap(loctestnum, loctesterr, heap, true);
        lasd::HeapVec<double> heap2(heap);
        EqualLinear(loctestnum, loctesterr, heap, heap2, true);
        Empty(loctestnum, loctesterr, heap, false);
        Size(loctestnum, loctesterr, heap, true, 14);

        Fold(loctestnum, loctesterr, heap2, true, &FoldAdd<double>, 0, 139);
        FoldPostOrder(loctestnum, loctesterr, heap2, true, &FoldAdd<double>, 0, 139);
        FoldPreOrder(loctestnum, loctesterr, heap2, true, &FoldAdd<double>, 0, 139);

        Map(loctestnum, loctesterr, heap2, true, &MapIncrement<double>);
        MapPostOrder(loctestnum, loctesterr, heap2, true, &MapIncrement<double>);
        MapPreOrder(loctestnum, loctesterr, heap2, true, &MapIncrement<double>);
        TraversePreOrder(loctestnum, loctesterr, heap, true, &TraversePrint<double>);
        heap.Clear();

        Size(loctestnum, loctesterr, heap, true, 0);

    } catch(...) {
        loctestnum++;
        loctesterr++;
        cout << endl << "Unmanaged error! " << endl;
    }
    cout << "End of Heap<double> Test! (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << endl;
    testnum += loctestnum;
    testerr += loctesterr;
}

void testHeapString(uint & testnum, uint & testerr) {
    uint loctestnum = 0, loctesterr = 0;
    cout << endl << "Begin of Heap<string> Test:" << endl;
    try {

        lasd::Vector<string> vec(14);
        SetAt(loctestnum, loctesterr, vec, true, 0, string("A"));
        SetAt(loctestnum, loctesterr, vec, true, 1, string("F"));
        SetAt(loctestnum, loctesterr, vec, true, 2, string("H"));
        SetAt(loctestnum, loctesterr, vec, true, 3, string("A"));
        SetAt(loctestnum, loctesterr, vec, true, 4, string("T"));
        SetAt(loctestnum, loctesterr, vec, true, 5, string("L"));
        SetAt(loctestnum, loctesterr, vec, true, 6, string("A"));
        SetAt(loctestnum, loctesterr, vec, true, 7, string("I"));
        SetAt(loctestnum, loctesterr, vec, true, 8, string("P"));
        SetAt(loctestnum, loctesterr, vec, true, 9, string("L"));
        SetAt(loctestnum, loctesterr, vec, true, 10, string("Z"));
        SetAt(loctestnum, loctesterr, vec, true, 11, string("X"));
        SetAt(loctestnum, loctesterr, vec, true, 12, string("Q"));
        SetAt(loctestnum, loctesterr, vec, true, 13, string("J")); 

        lasd::HeapVec<string> heap(vec);

        TraversePreOrder(loctestnum, loctesterr, heap, true, &TraversePrint<string>);
        TraversePostOrder(loctestnum, loctesterr, heap, true, &TraversePrint<string>);

        MapPreOrder(loctestnum, loctesterr, heap, true, [](string & str) {
            MapStringAppend(str, string("*"));
        });
        MapPreOrder(loctestnum, loctesterr, heap, true, [](string & str) {
            MapStringAppend(str, string(" "));
        });

        TraversePreOrder(loctestnum, loctesterr, heap, true, &TraversePrint<string>);
        TraversePostOrder(loctestnum, loctesterr, heap, true, &TraversePrint<string>);

        FoldPostOrder(loctestnum, loctesterr, heap, true, &FoldStringConcatenate, string("?"), string("?A* H* L* F* A* A* I* J* Q* L* P* X* T* Z* "));
        FoldPreOrder(loctestnum, loctesterr, heap, true, &FoldStringConcatenate, string("?"), string("?Z* T* X* P* L* Q* J* I* A* A* F* L* H* A* "));
        IsHeap(loctestnum, loctesterr, heap, true);

        heap.Sort();
        IsHeap(loctestnum, loctesterr, heap, false);

        TraversePreOrder(loctestnum, loctesterr, heap, true, &TraversePrint<string>);
        TraversePostOrder(loctestnum, loctesterr, heap, true, &TraversePrint<string>);

        FoldPostOrder(loctestnum, loctesterr, heap, true, &FoldStringConcatenate, string("?"), string("?Z* X* T* Q* P* L* L* J* I* H* F* A* A* A* "));
        FoldPreOrder(loctestnum, loctesterr, heap, true, &FoldStringConcatenate, string("?"), string("?A* A* A* F* H* I* J* L* L* P* Q* T* X* Z* "));

        heap.Heapify();

        TraversePreOrder(loctestnum, loctesterr, heap, true, &TraversePrint<string>);
        TraversePostOrder(loctestnum, loctesterr, heap, true, &TraversePrint<string>);

        FoldPostOrder(loctestnum, loctesterr, heap, true, &FoldStringConcatenate, string("?"), string("?A* I* A* H* A* L* F* J* T* P* L* X* Q* Z* "));
        FoldPreOrder(loctestnum, loctesterr, heap, true, &FoldStringConcatenate, string("?"), string("?Z* Q* X* L* P* T* J* F* L* A* H* A* I* A* "));

    } catch(...) {
        loctestnum++;
        loctesterr++;
        cout << endl << "Unmanaged error! " << endl;
    }
    cout << "End of Heap<string> Test! (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << endl;
    testnum += loctestnum;
    testerr += loctesterr;
}

/* ************************************************************************** */

void testPQInt(uint & testnum, uint & testerr) {
    uint loctestnum = 0, loctesterr = 0;
    cout << endl << "Begin of PQ<int> Test:" << endl;
    try {
        //Pq vuota
        lasd::PQHeap<int> pqEmpty;
        lasd::PQHeap<int> pqEmpty1;

        pqEmpty1 = pqEmpty1;
        Traverse(loctestnum, loctesterr, pqEmpty1, true, &TraversePrint<int>);
        TraversePostOrder(loctestnum, loctesterr, pqEmpty1, true, &TraversePrint<int>);
        TraversePreOrder(loctestnum, loctesterr, pqEmpty1, true, &TraversePrint<int>);

        Size(loctestnum, loctesterr, pqEmpty1, true, 0);
        Empty(loctestnum, loctesterr, pqEmpty1, true);
        Clear(loctestnum, loctesterr, pqEmpty1);


        Fold(loctestnum, loctesterr, pqEmpty1, true, &FoldAdd<int>, 0, 0);
        FoldPreOrder(loctestnum, loctesterr, pqEmpty1, true, &FoldAdd<int>, 0, 0);
        FoldPostOrder(loctestnum, loctesterr, pqEmpty1, true, &FoldAdd<int>, 0, 0);


        GetBack(loctestnum, loctesterr, pqEmpty1, false, 2);
        GetFront(loctestnum, loctesterr, pqEmpty1, false, 2);
        GetAt(loctestnum, loctesterr, pqEmpty1, false, 2, 0);
        GetAt(loctestnum, loctesterr, pqEmpty1, false, 0, 0);


        Exists(loctestnum, loctesterr, pqEmpty1, false, 2);
        EqualLinear(loctestnum, loctesterr, pqEmpty1, pqEmpty, true);
        Tip(loctestnum, loctesterr, pqEmpty, false, 10);
        RemoveTip(loctestnum, loctesterr, pqEmpty, false);
        TipNRemove(loctestnum, loctesterr, pqEmpty, false, 9);

        Insert(loctestnum, loctesterr, pqEmpty, 5);
        Insert(loctestnum, loctesterr, pqEmpty, std::move(6));
        Change(loctestnum, loctesterr, pqEmpty, false, 10, 7);
        Change(loctestnum, loctesterr, pqEmpty, true, 0, std::move(8));


        Traverse(loctestnum, loctesterr, pqEmpty1, true, &TraversePrint<int>);

        lasd::Vector<int> vec(14);
        SetAt(loctestnum, loctesterr, vec, true, 0, 5);
        SetAt(loctestnum, loctesterr, vec, true, 1, 2);
        SetAt(loctestnum, loctesterr, vec, true, 2, 1);
        SetAt(loctestnum, loctesterr, vec, true, 3, 4);
        SetAt(loctestnum, loctesterr, vec, true, 4, 0);
        SetAt(loctestnum, loctesterr, vec, true, 5, 5);
        SetAt(loctestnum, loctesterr, vec, true, 6, 0);
        SetAt(loctestnum, loctesterr, vec, true, 7, 8);
        SetAt(loctestnum, loctesterr, vec, true, 8, 12);
        SetAt(loctestnum, loctesterr, vec, true, 9, 11);
        SetAt(loctestnum, loctesterr, vec, true, 10, 2);
        SetAt(loctestnum, loctesterr, vec, true, 11, 12);
        SetAt(loctestnum, loctesterr, vec, true, 12, 92);
        SetAt(loctestnum, loctesterr, vec, true, 13, 69);

        lasd::PQHeap<int> pq(vec);
        lasd::PQHeap<int> pq22(std::move(vec));
        Insert(loctestnum, loctesterr, pq22, 0);
        Insert(loctestnum, loctesterr, pq22, 25);
        Insert(loctestnum, loctesterr, pq22, 41);
        Insert(loctestnum, loctesterr, pq22, 3);
        Insert(loctestnum, loctesterr, pq22, 22);
        Insert(loctestnum, loctesterr, pq22, 91);
        Insert(loctestnum, loctesterr, pq22, 1);
        Insert(loctestnum, loctesterr, pq22, 11);


        Traverse(loctestnum, loctesterr, pq, true, &TraversePrint<int>);
        TraversePreOrder(loctestnum, loctesterr, pq, true, &TraversePrint<int>);
        TraversePostOrder(loctestnum, loctesterr, pq, true, &TraversePrint<int>);

        Tip(loctestnum, loctesterr, pq, true, 92);
        RemoveTip(loctestnum, loctesterr, pq, true);

        TraversePreOrder(loctestnum, loctesterr, pq, true, &TraversePrint<int>);
        TraversePostOrder(loctestnum, loctesterr, pq, true, &TraversePrint<int>);

        Tip(loctestnum, loctesterr, pq, true, 69);
        RemoveTip(loctestnum, loctesterr, pq, true);
        TipNRemove(loctestnum, loctesterr, pq, true, 12);
        TipNRemove(loctestnum, loctesterr, pq, true, 12);
        TipNRemove(loctestnum, loctesterr, pq, true, 11);

        TraversePreOrder(loctestnum, loctesterr, pq, true, &TraversePrint<int>);
        TraversePostOrder(loctestnum, loctesterr, pq, true, &TraversePrint<int>);

        Insert(loctestnum, loctesterr, pq, 5);

        TraversePreOrder(loctestnum, loctesterr, pq, true, &TraversePrint<int>);
        TraversePostOrder(loctestnum, loctesterr, pq, true, &TraversePrint<int>);
        cout << pq22[1] << endl;
        Tip(loctestnum, loctesterr, pq, true, 8);
        TraversePreOrder(loctestnum, loctesterr, pq, true, &TraversePrint<int>);

        RemoveTip(loctestnum, loctesterr, pq, true);
        TraversePreOrder(loctestnum, loctesterr, pq, true, &TraversePrint<int>);

        TipNRemove(loctestnum, loctesterr, pq, true, 5);
        TipNRemove(loctestnum, loctesterr, pq, true, 5);
        TipNRemove(loctestnum, loctesterr, pq, true, 5);

        TraversePreOrder(loctestnum, loctesterr, pq, true, &TraversePrint<int>);
        TraversePostOrder(loctestnum, loctesterr, pq, true, &TraversePrint<int>);

        Insert(loctestnum, loctesterr, pq, 3);

        TraversePreOrder(loctestnum, loctesterr, pq, true, &TraversePrint<int>);
        TraversePostOrder(loctestnum, loctesterr, pq, true, &TraversePrint<int>);

        TipNRemove(loctestnum, loctesterr, pq, true, 4);
        TipNRemove(loctestnum, loctesterr, pq, true, 3);
        TipNRemove(loctestnum, loctesterr, pq, true, 2);
        Tip(loctestnum, loctesterr, pq, true, 2);
        RemoveTip(loctestnum, loctesterr, pq, true);
        TipNRemove(loctestnum, loctesterr, pq, true, 1);

        TraversePreOrder(loctestnum, loctesterr, pq, true, &TraversePrint<int>);
        TraversePostOrder(loctestnum, loctesterr, pq, true, &TraversePrint<int>);

        Insert(loctestnum, loctesterr, pq, 10);

        TraversePreOrder(loctestnum, loctesterr, pq, true, &TraversePrint<int>);
        TraversePostOrder(loctestnum, loctesterr, pq, true, &TraversePrint<int>);

        TipNRemove(loctestnum, loctesterr, pq, true, 10);
        TipNRemove(loctestnum, loctesterr, pq, true, 0);

        TraversePreOrder(loctestnum, loctesterr, pq, true, &TraversePrint<int>);
        TraversePostOrder(loctestnum, loctesterr, pq, true, &TraversePrint<int>);

        Insert(loctestnum, loctesterr, pq, 8);

        TraversePreOrder(loctestnum, loctesterr, pq, true, &TraversePrint<int>);
        TraversePostOrder(loctestnum, loctesterr, pq, true, &TraversePrint<int>);

        Exists(loctestnum, loctesterr, pq, true, 8);
        Exists(loctestnum, loctesterr, pq, false, 12);

        GetAt(loctestnum, loctesterr, pq, true, 0, 8);

        TipNRemove(loctestnum, loctesterr, pq, true, 8);
        TipNRemove(loctestnum, loctesterr, pq, true, 0);
        RemoveTip(loctestnum, loctesterr, pq, false);

        Insert(loctestnum, loctesterr, pq, 1);
        Insert(loctestnum, loctesterr, pq, 5);
        Insert(loctestnum, loctesterr, pq, 0);
        Insert(loctestnum, loctesterr, pq, 4);
        Insert(loctestnum, loctesterr, pq, 2);
        Insert(loctestnum, loctesterr, pq, 3);
        Insert(loctestnum, loctesterr, pq, 7);
        Insert(loctestnum, loctesterr, pq, 6);

        TraversePreOrder(loctestnum, loctesterr, pq, true, &TraversePrint<int>);
        TraversePostOrder(loctestnum, loctesterr, pq, true, &TraversePrint<int>);

        Change(loctestnum, loctesterr, pq,  true,  0, 8);

        TraversePreOrder(loctestnum, loctesterr, pq, true, &TraversePrint<int>);
        TraversePostOrder(loctestnum, loctesterr, pq, true, &TraversePrint<int>);

        Insert(loctestnum, loctesterr, pq, 1);
        Insert(loctestnum, loctesterr, pq, 0);

        TraversePreOrder(loctestnum, loctesterr, pq, true, &TraversePrint<int>);
        TraversePostOrder(loctestnum, loctesterr, pq, true, &TraversePrint<int>);

        Change(loctestnum, loctesterr, pq,  true,  1, 2);

        TraversePreOrder(loctestnum, loctesterr, pq, true, &TraversePrint<int>);
        TraversePostOrder(loctestnum, loctesterr, pq, true, &TraversePrint<int>);

        Change(loctestnum, loctesterr, pq,  true,  6, 6);

        Traverse(loctestnum, loctesterr, pq, true, &TraversePrint<int>);
        TraversePreOrder(loctestnum, loctesterr, pq, true, &TraversePrint<int>);
        TraversePostOrder(loctestnum, loctesterr, pq, true, &TraversePrint<int>);

        ChangePQM(loctestnum, loctesterr, pq, 8, 10);

        TraversePreOrder(loctestnum, loctesterr, pq, true, &TraversePrint<int>);
        TraversePostOrder(loctestnum, loctesterr, pq, true, &TraversePrint<int>);

        Fold(loctestnum, loctesterr, pq, true, &FoldAdd<int>, 0, 38);
        FoldPreOrder(loctestnum, loctesterr, pq, true, &FoldAdd<int>, 0, 38);
        FoldPostOrder(loctestnum, loctesterr, pq, true, &FoldAdd<int>, 0, 38);

        Empty(loctestnum, loctesterr, pq, false);
        Size(loctestnum, loctesterr, pq, true, 10);

        lasd::PQHeap<int> pq1(std::move(pq));

        Empty(loctestnum, loctesterr, pq, true);
        Size(loctestnum, loctesterr, pq, true, 0);

        Empty(loctestnum, loctesterr, pq1, false);
        Size(loctestnum, loctesterr, pq1, true, 10);

        EqualLinear(loctestnum, loctesterr, pq, pq1, false);

        TipNRemove(loctestnum, loctesterr, pq1, true, 10);
        TipNRemove(loctestnum, loctesterr, pq1, true, 8);
        Insert(loctestnum, loctesterr, pq1, 11);
        TipNRemove(loctestnum, loctesterr, pq1, true, 11);

        EqualLinear(loctestnum, loctesterr, pq, pq1, false);

        Empty(loctestnum, loctesterr, pq1, false);
        Size(loctestnum, loctesterr, pq1, true, 8);

        pq = pq1;

        EqualLinear(loctestnum, loctesterr, pq, pq1, true);

        lasd::PQHeap<int> pq2(pq);

        EqualLinear(loctestnum, loctesterr, pq1, pq2, true);

        TraversePreOrder(loctestnum, loctesterr, pq2, true, &TraversePrint<int>);
        TraversePostOrder(loctestnum, loctesterr, pq2, true, &TraversePrint<int>);

        TipNRemove(loctestnum, loctesterr, pq2, true, 6);

        TraversePreOrder(loctestnum, loctesterr, pq2, true, &TraversePrint<int>);
        TraversePostOrder(loctestnum, loctesterr, pq2, true, &TraversePrint<int>);
        Change(loctestnum, loctesterr, pq2,  true,  0, -1);

        TraversePreOrder(loctestnum, loctesterr, pq2, true, &TraversePrint<int>);
        TraversePostOrder(loctestnum, loctesterr, pq2, true, &TraversePrint<int>);

        TipNRemove(loctestnum, loctesterr, pq2, true, 4);

        Empty(loctestnum, loctesterr, pq1, false);
        Size(loctestnum, loctesterr, pq1, true, 8);
        try {
            pq1.Change(100, 12);
        } catch(std::exception & exc)  {
            std::cout << exc.what() << "\": "  << "!" << std::endl;
        }
        pq2 = std::move(pq1);

        Empty(loctestnum, loctesterr, pq1, false);
        Size(loctestnum, loctesterr, pq1, true, 6);
        pq1.Clear();
        Empty(loctestnum, loctesterr, pq2, false);
        Size(loctestnum, loctesterr, pq2, true, 8);
        Clear(loctestnum, loctesterr, pq2);
        try {
            pq2.Change(100, 12);
        } catch(std::exception & exc)  {
            std::cout << exc.what() << "\": "  << "!" << std::endl;
        }
    } catch(...) {
        loctestnum++;
        loctesterr++;
        cout << endl << "Unmanaged error! " << endl;
    }
    cout << "End of PQ<int> Test! (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << endl;
    testnum += loctestnum;
    testerr += loctesterr;
}

void testPQDouble(uint & testnum, uint & testerr) {
    uint loctestnum = 0, loctesterr = 0;
    cout << endl << "Begin of PQ<double> Test:" << endl;
    try {

        lasd::Vector<double> vec(14);
        SetAt(loctestnum, loctesterr, vec, true, 0, 3.2);
        SetAt(loctestnum, loctesterr, vec, true, 1, 4.0);
        SetAt(loctestnum, loctesterr, vec, true, 2, 2.6);
        SetAt(loctestnum, loctesterr, vec, true, 3, 0.4);
        SetAt(loctestnum, loctesterr, vec, true, 4, 1.5);
        SetAt(loctestnum, loctesterr, vec, true, 5, 5.8);
        SetAt(loctestnum, loctesterr, vec, true, 6, 10.12);
        SetAt(loctestnum, loctesterr, vec, true, 7, 8.3);
        SetAt(loctestnum, loctesterr, vec, true, 8, 0.9);
        SetAt(loctestnum, loctesterr, vec, true, 9, 11.45);
        SetAt(loctestnum, loctesterr, vec, true, 10, 7.26);
        SetAt(loctestnum, loctesterr, vec, true, 11, 9.1);
        SetAt(loctestnum, loctesterr, vec, true, 12, 3.65);
        SetAt(loctestnum, loctesterr, vec, true, 13, 6.37);

        lasd::PQHeap<double> pq(vec);
        lasd::PQHeap<double> pq22(std::move(vec));

        Insert(loctestnum, loctesterr, pq22, 0.23);
        Insert(loctestnum, loctesterr, pq22, 5.4);
        Insert(loctestnum, loctesterr, pq22, 1.18);
        Insert(loctestnum, loctesterr, pq22, 3.18);
        Insert(loctestnum, loctesterr, pq22, 2.9);
        Insert(loctestnum, loctesterr, pq22, 4.20);
        Insert(loctestnum, loctesterr, pq22, 6.3);


        Traverse(loctestnum, loctesterr, pq, true, &TraversePrint<double>);
        TraversePreOrder(loctestnum, loctesterr, pq, true, &TraversePrint<double>);
        TraversePostOrder(loctestnum, loctesterr, pq, true, &TraversePrint<double>);

        Tip(loctestnum, loctesterr, pq, true, 11.45);
        RemoveTip(loctestnum, loctesterr, pq, true);

        TraversePreOrder(loctestnum, loctesterr, pq, true, &TraversePrint<double>);
        TraversePostOrder(loctestnum, loctesterr, pq, true, &TraversePrint<double>);

        Tip(loctestnum, loctesterr, pq, true, 10.12);
        RemoveTip(loctestnum, loctesterr, pq, true);
        TipNRemove(loctestnum, loctesterr, pq, true, 9.1);
        TipNRemove(loctestnum, loctesterr, pq, true, 8.3);
        TipNRemove(loctestnum, loctesterr, pq, true, 7.26);

        TraversePreOrder(loctestnum, loctesterr, pq, true, &TraversePrint<double>);
        TraversePostOrder(loctestnum, loctesterr, pq, true, &TraversePrint<double>);

        Insert(loctestnum, loctesterr, pq, 5.27);

        TraversePreOrder(loctestnum, loctesterr, pq, true, &TraversePrint<double>);
        TraversePostOrder(loctestnum, loctesterr, pq, true, &TraversePrint<double>);
        Tip(loctestnum, loctesterr, pq, true, 6.37);
        TraversePreOrder(loctestnum, loctesterr, pq, true, &TraversePrint<double>);

        RemoveTip(loctestnum, loctesterr, pq, true);
        TraversePreOrder(loctestnum, loctesterr, pq, true, &TraversePrint<double>);

        TipNRemove(loctestnum, loctesterr, pq, true, 5.8);
        TipNRemove(loctestnum, loctesterr, pq, true, 5.27);
        TipNRemove(loctestnum, loctesterr, pq, true, 4.0);

        TraversePreOrder(loctestnum, loctesterr, pq, true, &TraversePrint<double>);
        TraversePostOrder(loctestnum, loctesterr, pq, true, &TraversePrint<double>);
        Insert(loctestnum, loctesterr, pq, 3.6);
        TraversePreOrder(loctestnum, loctesterr, pq, true, &TraversePrint<double>);
        TraversePostOrder(loctestnum, loctesterr, pq, true, &TraversePrint<double>);

        TipNRemove(loctestnum, loctesterr, pq, true, 3.65);
        TipNRemove(loctestnum, loctesterr, pq, true, 3.6);
        TipNRemove(loctestnum, loctesterr, pq, true, 3.2);
        Tip(loctestnum, loctesterr, pq, true, 2.6);
        RemoveTip(loctestnum, loctesterr, pq, true);
        TipNRemove(loctestnum, loctesterr, pq, true, 1.5);

        TraversePreOrder(loctestnum, loctesterr, pq, true, &TraversePrint<double>);
        TraversePostOrder(loctestnum, loctesterr, pq, true, &TraversePrint<double>);

        Insert(loctestnum, loctesterr, pq, 10.6);

        TraversePreOrder(loctestnum, loctesterr, pq, true, &TraversePrint<double>);
        TraversePostOrder(loctestnum, loctesterr, pq, true, &TraversePrint<double>);
        TipNRemove(loctestnum, loctesterr, pq, true, 10.6);
        TipNRemove(loctestnum, loctesterr, pq, true, 0.9);
        TraversePreOrder(loctestnum, loctesterr, pq, true, &TraversePrint<double>);
        TraversePostOrder(loctestnum, loctesterr, pq, true, &TraversePrint<double>);

        Insert(loctestnum, loctesterr, pq, 8.4);

        TraversePreOrder(loctestnum, loctesterr, pq, true, &TraversePrint<double>);
        TraversePostOrder(loctestnum, loctesterr, pq, true, &TraversePrint<double>);

        Exists(loctestnum, loctesterr, pq, true, 8.4);
        Exists(loctestnum, loctesterr, pq, false, 12.104);

        GetAt(loctestnum, loctesterr, pq, true, 0, 8.4);

        TipNRemove(loctestnum, loctesterr, pq, true, 8.4);
        TipNRemove(loctestnum, loctesterr, pq, true, 0.4);
        RemoveTip(loctestnum, loctesterr, pq, false);

        Insert(loctestnum, loctesterr, pq, 7.0);
        Insert(loctestnum, loctesterr, pq, 6.9);
        Insert(loctestnum, loctesterr, pq, 5.0);
        Insert(loctestnum, loctesterr, pq, 4.1);
        Insert(loctestnum, loctesterr, pq, 3.2);
        Insert(loctestnum, loctesterr, pq, 2.5);
        Insert(loctestnum, loctesterr, pq, 1.0);
        Insert(loctestnum, loctesterr, pq, 0.1);

        TraversePreOrder(loctestnum, loctesterr, pq, true, &TraversePrint<double>);
        TraversePostOrder(loctestnum, loctesterr, pq, true, &TraversePrint<double>);
        Change(loctestnum, loctesterr, pq, true,  0, 0.2);
        TraversePreOrder(loctestnum, loctesterr, pq, true, &TraversePrint<double>);
        TraversePostOrder(loctestnum, loctesterr, pq, true, &TraversePrint<double>);

        Insert(loctestnum, loctesterr, pq, 1.3);
        Insert(loctestnum, loctesterr, pq, 0.9);

        TraversePreOrder(loctestnum, loctesterr, pq, true, &TraversePrint<double>);
        TraversePostOrder(loctestnum, loctesterr, pq, true, &TraversePrint<double>);
        Change(loctestnum, loctesterr, pq, true, 1, 2.4);
        TraversePreOrder(loctestnum, loctesterr, pq, true, &TraversePrint<double>);
        TraversePostOrder(loctestnum, loctesterr, pq, true, &TraversePrint<double>);

        ChangePQM(loctestnum, loctesterr, pq, 6, 6.90);

        Traverse(loctestnum, loctesterr, pq, true, &TraversePrint<double>);
        TraversePreOrder(loctestnum, loctesterr, pq, true, &TraversePrint<double>);
        TraversePostOrder(loctestnum, loctesterr, pq, true, &TraversePrint<double>);
        Change(loctestnum, loctesterr, pq, true, 8, std::move(10.0));
        TraversePreOrder(loctestnum, loctesterr, pq, true, &TraversePrint<double>);
        TraversePostOrder(loctestnum, loctesterr, pq, true, &TraversePrint<double>);

        Fold(loctestnum, loctesterr, pq, true, &FoldAdd<double>, 0, 35);
        FoldPreOrder(loctestnum, loctesterr, pq, true, &FoldAdd<double>, 0, 35);
        FoldPostOrder(loctestnum, loctesterr, pq, true, &FoldAdd<double>, 0, 35);

        Empty(loctestnum, loctesterr, pq, false);
        Size(loctestnum, loctesterr, pq, true, 10);

        lasd::PQHeap<double> pq1(std::move(pq));

        Empty(loctestnum, loctesterr, pq, true);
        Size(loctestnum, loctesterr, pq, true, 0);

        Empty(loctestnum, loctesterr, pq1, false);
        Size(loctestnum, loctesterr, pq1, true, 10);

        EqualLinear(loctestnum, loctesterr, pq, pq1, false);

        TipNRemove(loctestnum, loctesterr, pq1, true, 10.0);
        TipNRemove(loctestnum, loctesterr, pq1, true, 6.9);
        Insert(loctestnum, loctesterr, pq1, 11.0);
        TipNRemove(loctestnum, loctesterr, pq1, true, 11.0);

        EqualLinear(loctestnum, loctesterr, pq, pq1, false);

        Empty(loctestnum, loctesterr, pq1, false);
        Size(loctestnum, loctesterr, pq1, true, 8);

        pq = pq1;

        EqualLinear(loctestnum, loctesterr, pq, pq1, true);

        lasd::PQHeap<double> pq2(pq);

        EqualLinear(loctestnum, loctesterr, pq1, pq2, true);

        TraversePreOrder(loctestnum, loctesterr, pq2, true, &TraversePrint<double>);
        TraversePostOrder(loctestnum, loctesterr, pq2, true, &TraversePrint<double>);
        TipNRemove(loctestnum, loctesterr, pq2, true, 6.9);
        TraversePreOrder(loctestnum, loctesterr, pq2, true, &TraversePrint<double>);
        TraversePostOrder(loctestnum, loctesterr, pq2, true, &TraversePrint<double>);

        ChangePQM(loctestnum, loctesterr, pq2, 0, -1.0);

        TraversePreOrder(loctestnum, loctesterr, pq2, true, &TraversePrint<double>);
        TraversePostOrder(loctestnum, loctesterr, pq2, true, &TraversePrint<double>);

        TipNRemove(loctestnum, loctesterr, pq2, true, 3.2);

        Empty(loctestnum, loctesterr, pq1, false);
        Size(loctestnum, loctesterr, pq1, true, 8);

        pq2 = std::move(pq1);

        Empty(loctestnum, loctesterr, pq1, false);
        Size(loctestnum, loctesterr, pq1, true, 6);
        pq1.Clear();
        Empty(loctestnum, loctesterr, pq2, false);
        Size(loctestnum, loctesterr, pq2, true, 8);
        Clear(loctestnum, loctesterr, pq2);

    } catch(...) {
        loctestnum++;
        loctesterr++;
        cout << endl << "Unmanaged error! " << endl;
    }
    cout << "End of PQ<double> Test! (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << endl;
    testnum += loctestnum;
    testerr += loctesterr;
}

void testPQString(uint & testnum, uint & testerr) {
    uint loctestnum = 0, loctesterr = 0;
    cout << endl << "Begin of PQ<string> Test:" << endl;
    try {

        lasd::Vector<string> vec(14);
        SetAt(loctestnum, loctesterr, vec, true, 0, string("F"));
        SetAt(loctestnum, loctesterr, vec, true, 1, string("D"));
        SetAt(loctestnum, loctesterr, vec, true, 2, string("K"));
        SetAt(loctestnum, loctesterr, vec, true, 3, string("A"));
        SetAt(loctestnum, loctesterr, vec, true, 4, string("C"));
        SetAt(loctestnum, loctesterr, vec, true, 5, string("E"));
        SetAt(loctestnum, loctesterr, vec, true, 6, string("A"));
        SetAt(loctestnum, loctesterr, vec, true, 7, string("H"));
        SetAt(loctestnum, loctesterr, vec, true, 8, string("K"));
        SetAt(loctestnum, loctesterr, vec, true, 9, string("L"));
        SetAt(loctestnum, loctesterr, vec, true, 10, string("I"));
        SetAt(loctestnum, loctesterr, vec, true, 11, string("D"));
        SetAt(loctestnum, loctesterr, vec, true, 12, string("G"));
        SetAt(loctestnum, loctesterr, vec, true, 13, string("J"));

        lasd::PQHeap<string> pq(vec);
        lasd::PQHeap<string> pq22(std::move(vec));
        InsertPQM(loctestnum, loctesterr, pq22, string("c"));
        InsertPQM(loctestnum, loctesterr, pq22, string("d"));
        InsertPQM(loctestnum, loctesterr, pq22, string("g"));
        InsertPQM(loctestnum, loctesterr, pq22, string("f"));
        InsertPQM(loctestnum, loctesterr, pq22, string("e"));
        InsertPQM(loctestnum, loctesterr, pq22, string("b"));
        InsertPQM(loctestnum, loctesterr, pq22, string("a"));

        Traverse(loctestnum, loctesterr, pq, true, &TraversePrint<string>);
        TraversePreOrder(loctestnum, loctesterr, pq, true, &TraversePrint<string>);
        TraversePostOrder(loctestnum, loctesterr, pq, true, &TraversePrint<string>);

        FoldPreOrder(loctestnum, loctesterr, pq, true, &FoldStringConcatenate, string("?"), string("?LKKHIGJFACDDEA"));
        FoldPostOrder(loctestnum, loctesterr, pq, true, &FoldStringConcatenate, string("?"), string("?AEDDCAFJGIHKKL"));

        Tip(loctestnum, loctesterr, pq, true, string("L"));
        RemoveTip(loctestnum, loctesterr, pq, true);

        TraversePreOrder(loctestnum, loctesterr, pq, true, &TraversePrint<string>);
        TraversePostOrder(loctestnum, loctesterr, pq, true, &TraversePrint<string>);

        Tip(loctestnum, loctesterr, pq, true, string("K"));
        RemoveTip(loctestnum, loctesterr, pq, true);
        Insert(loctestnum, loctesterr, pq, string("J"));
        Insert(loctestnum, loctesterr, pq, string("K"));
        TipNRemove(loctestnum, loctesterr, pq, true, string("K"));
        TipNRemove(loctestnum, loctesterr, pq, true, string("K"));
        TipNRemove(loctestnum, loctesterr, pq, true, string("J"));

        TraversePreOrder(loctestnum, loctesterr, pq, true, &TraversePrint<string>);
        TraversePostOrder(loctestnum, loctesterr, pq, true, &TraversePrint<string>);

        FoldPreOrder(loctestnum, loctesterr, pq, true, &FoldStringConcatenate, string("?"), string("?JIGHDDEFACA"));
        FoldPostOrder(loctestnum, loctesterr, pq, true, &FoldStringConcatenate, string("?"), string("?ACAFEDDHGIJ"));
        Insert(loctestnum, loctesterr, pq, string("F"));
        TraversePreOrder(loctestnum, loctesterr, pq, true, &TraversePrint<string>);
        TraversePostOrder(loctestnum, loctesterr, pq, true, &TraversePrint<string>);

        FoldPreOrder(loctestnum, loctesterr, pq, true, &FoldStringConcatenate, string("?"), string("?JIGHDFEFACAD"));
        FoldPostOrder(loctestnum, loctesterr, pq, true, &FoldStringConcatenate, string("?"), string("?DACAFEFDHGIJ"));

        Change(loctestnum, loctesterr, pq, true, 4, string("X"));

        TraversePreOrder(loctestnum, loctesterr, pq, true, &TraversePrint<string>);
        TraversePostOrder(loctestnum, loctesterr, pq, true, &TraversePrint<string>);

        FoldPreOrder(loctestnum, loctesterr, pq, true, &FoldStringConcatenate, string("?"), string("?XJGHIFEFACAD"));
        FoldPostOrder(loctestnum, loctesterr, pq, true, &FoldStringConcatenate, string("?"), string("?DACAFEFIHGJX"));
        Change(loctestnum, loctesterr, pq, true, 1, string("A"));
        TraversePreOrder(loctestnum, loctesterr, pq, true, &TraversePrint<string>);
        TraversePostOrder(loctestnum, loctesterr, pq, true, &TraversePrint<string>);

        FoldPreOrder(loctestnum, loctesterr, pq, true, &FoldStringConcatenate, string("?"), string("?XIGHCFEFAAAD"));
        FoldPostOrder(loctestnum, loctesterr, pq, true, &FoldStringConcatenate, string("?"), string("?DAAAFEFCHGIX"));
        ChangePQM(loctestnum, loctesterr, pq, 2, string("B"));
        TraversePreOrder(loctestnum, loctesterr, pq, true, &TraversePrint<string>);
        TraversePostOrder(loctestnum, loctesterr, pq, true, &TraversePrint<string>);

        FoldPreOrder(loctestnum, loctesterr, pq, true, &FoldStringConcatenate, string("?"), string("?XIFHCDEFAAAB"));
        FoldPostOrder(loctestnum, loctesterr, pq, true, &FoldStringConcatenate, string("?"), string("?BAAAFEDCHFIX"));

        Exists(loctestnum, loctesterr, pq, true, string("B"));
        Exists(loctestnum, loctesterr, pq, false, string("N"));

        GetAt(loctestnum, loctesterr, pq, true, 0, string("X"));

        Empty(loctestnum, loctesterr, pq, false);
        Size(loctestnum, loctesterr, pq, true, 12);

        lasd::PQHeap<string> pq1(std::move(pq));

        Empty(loctestnum, loctesterr, pq, true);
        Size(loctestnum, loctesterr, pq, true, 0);

        Empty(loctestnum, loctesterr, pq1, false);
        Size(loctestnum, loctesterr, pq1, true, 12);

        EqualLinear(loctestnum, loctesterr, pq, pq1, false);

        TipNRemove(loctestnum, loctesterr, pq1, true, string("X"));
        TipNRemove(loctestnum, loctesterr, pq1, true, string("I"));
        Insert(loctestnum, loctesterr, pq1, string("B"));
        TipNRemove(loctestnum, loctesterr, pq1, true, string("H"));

        EqualLinear(loctestnum, loctesterr, pq, pq1, false);

        Empty(loctestnum, loctesterr, pq1, false);
        Size(loctestnum, loctesterr, pq1, true, 10);

        pq = pq1;

        EqualLinear(loctestnum, loctesterr, pq, pq1, true);

        lasd::PQHeap<string> pq2(pq);

        EqualLinear(loctestnum, loctesterr, pq1, pq2, true);

        TraversePostOrder(loctestnum, loctesterr, pq2, true, &TraversePrint<string>);
        TraversePreOrder(loctestnum, loctesterr, pq2, true, &TraversePrint<string>);
        TipNRemove(loctestnum, loctesterr, pq2, true, string("F"));
        TraversePostOrder(loctestnum, loctesterr, pq2, true, &TraversePrint<string>);
        TraversePreOrder(loctestnum, loctesterr, pq2, true, &TraversePrint<string>);

        Change(loctestnum, loctesterr, pq2, true, 0, string("B"));

        TraversePreOrder(loctestnum, loctesterr, pq2, true, &TraversePrint<string>);
        TraversePostOrder(loctestnum, loctesterr, pq2, true, &TraversePrint<string>);

        TipNRemove(loctestnum, loctesterr, pq2, true, string("E"));

        Empty(loctestnum, loctesterr, pq1, false);
        Size(loctestnum, loctesterr, pq1, true, 10);

        pq2 = std::move(pq1);

        Empty(loctestnum, loctesterr, pq1, false);
        Size(loctestnum, loctesterr, pq1, true, 8);
        pq1.Clear();
        Empty(loctestnum, loctesterr, pq2, false);
        Size(loctestnum, loctesterr, pq2, true, 10);
        Clear(loctestnum, loctesterr, pq2);
    } catch(...) {
        loctestnum++;
        loctesterr++;
        cout << endl << "Unmanaged error! " << endl;
    }
    cout << "End of PQ<string> Test! (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << endl;
    testnum += loctestnum;
    testerr += loctesterr;
}

/* ************************************************************************** */

void mytest() { 
    lasd::Vector<int> vec(7);
    uint testnum1 = 0;
    uint testerr1 = 0;
    uint testnum2 = 0;
    uint testerr2 = 0;
    
    // TEMPLATE 1 TEST
    testVector(testnum1, testerr1); 
    testList(testnum1, testerr1);
    testSetInt(testnum1, testerr1);
    testSetFloat(testnum1, testerr1);
    testSetString(testnum1, testerr1);

    // TEMPLATE 2 TEST
    testHeapInt(testnum2, testerr2);
    testHeapDouble(testnum2, testerr2);
    testHeapString(testnum2, testerr2);
    testPQInt(testnum2, testerr2);
    testPQDouble(testnum2, testerr2);
    testPQString(testnum2, testerr2);


    // Test messages
    cout << endl << "Test of Template 1 (Errors/Tests: " << testerr1 << "/" << testnum1 << ")" << endl;
    cout << endl << "Test of Template 2 (Errors/Tests: " << testerr2 << "/" << testnum2 << ")" << endl;

    // THIS IS THE END  
}
}