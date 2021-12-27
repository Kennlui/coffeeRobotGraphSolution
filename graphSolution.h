//  graphSolution.h
//  Coffee Robot Problem
//  Graph Solution G = (V, E)
//  Created by Kenn Lui on 2021-11-21.
//  kenn_lui@sfu.ca

#ifndef graphSolution_h
#define graphSolution_h
#include <vector>

class Edge;

class Vertex
{
    private: // data elements
        int x;
        int y;
        bool c = false;
    
    public:
        Vertex(); // default constructor
        Vertex(const Vertex &); // copy constructor
    
    public: // accessors
        int getX() const;
        int getY() const;
        bool getC() const;
        
    public: // mutators
        void setXY(int, int);
        void setXYfromArray(int [2]);
        void placeC();
        void resetVertex();

    public: // comparison operator
        bool operator==(const Vertex &);
    
    public: // print to console
        void printVertex();
        void printNeighbours(std::vector<Edge>);
        static void printVertices(std::vector<Vertex>);
    
    public: // scan down or left
        Vertex scanDown(std::vector<Vertex>);
        Vertex scanLeft(std::vector<Vertex>);
    
    public: // find
        static Vertex findVertex(int, int, std::vector<Vertex>);
    
    public: // onboarding
        static void onboarding(int [][2], int, int, int &, Vertex *, Edge *, std::vector<Vertex> &, std::vector<Edge> &, int);
};

Vertex::Vertex()
{
    this -> x = -1;
    this -> y = -1;
    this -> c = false;
}

Vertex::Vertex(const Vertex & obj)
{
    this -> x = obj.x;
    this -> y = obj.y;
    this -> c = obj.c;
}

int Vertex::getX() const
{
    return this -> x;
}

int Vertex::getY() const
{
    return this -> y;
}

bool Vertex::getC() const
{
    return this -> c;
}

void Vertex::setXY(int n1, int n2)
{
    this -> x = n1;
    this -> y = n2;
}

void Vertex::setXYfromArray(int a [2])
{
    this -> x = *(a);
    this -> y = *(a + 1);
}

void Vertex::placeC()
{
    this -> c = true;
}

void Vertex::resetVertex()
{
    this -> x = -1;
    this -> y = -1;
    this -> c = false;
}

bool Vertex::operator==(const Vertex & right)
{
    bool rv = (this -> x == right.x) &&
              (this -> y == right.y) &&
              (this -> c == right.c);
    return rv;
}

void Vertex::printVertex()
{
    char coffee = 'n';
    if (this -> c)
        coffee = 'c';
    std::cout << "[ ("<< x << ", " << y << "), " << coffee <<" ]";
}

// scan down in search of neighbours
// this assumes that columns (not rows) are onboarded

Vertex Vertex::scanDown(std::vector<Vertex> U)
{
    return findVertex((this -> x), (this -> y - 1), U);
}

// scan left in search of neighbours
// this assumes that columns are onboarded left to right

Vertex Vertex::scanLeft(std::vector<Vertex> U)
{
    return findVertex((this -> x - 1), (this -> y), U);
}

Vertex Vertex::findVertex(int x, int y, std::vector<Vertex> U)
{
    Vertex dummy;
    std::vector<Vertex>::iterator it;
    
    it = U.begin();
    for (; it < U.end(); it++)
        if ((it) -> getX() == x)
            if ((it) -> getY() == y)
                return *it;
    return dummy;
}

class Edge : public Vertex
{
    private: // data elements
        Vertex u;
        Vertex v;
    
    public: // accessor
        Vertex getU() const;
        Vertex getV() const;
    
    public: // mutator
        void setUV(Vertex, Vertex);
        void setUVfromArray(Vertex [2]);

    public: // print to console
        void printEdge();
        static void printEdges(std::vector<Edge>);
    
    public: // find
        static Vertex findNeighbours(std::vector<Edge>, Vertex, std::vector<Vertex> &);
    
    public: // add edge (pairwise)
        static void addEdgePair(Edge [2], std::vector<Edge> &, Vertex, Vertex);
    
    public: //
        static void makeEdgesAndVertices(std::vector<Vertex> &, Vertex *, std::vector<Edge> &, Edge *, int, int);
};

Vertex Edge::getU() const
{
    return this -> u;
}

Vertex Edge::getV() const
{
    return this -> v;
}

void Edge::setUV(Vertex o1, Vertex o2)
{
    this -> u = o1;
    this -> v = o2;
}

void Edge::setUVfromArray(Vertex a [2])
{
    this -> u = *(a);
    this -> v = *(a+1);
}

void Edge::printEdge()
{
    std::cout << "{ ";
    this -> u.printVertex();
    std::cout << ", ";
    this -> v.printVertex();
    std::cout << " }";
}

// basic neighbour search function to populate neighbours in all directions

Vertex Edge::findNeighbours(std::vector<Edge> edges, Vertex target, std::vector<Vertex> & output)
{
    Vertex dummy;
    std::vector<Edge>::iterator ite;
    ite = edges.begin();
    for (; ite < edges.end(); ite++)
        if (target.getX() == ite -> getU().getX())
            if (target.getY() == ite -> getU().getY())
            {
                dummy = ite -> getV();
                output.push_back(dummy);
            }
    return dummy;
}

void Vertex::printNeighbours(std::vector<Edge> edgeVector)
{
    std::vector<Vertex> n;
    std::vector<Vertex>::iterator it;
    
    std::cout << "\nResult of neighbour search for ";
    this -> printVertex();
    std::cout << ":  ";
    Edge::findNeighbours(edgeVector, *this, n);
    std::cout << n.size() << " objects in n vector.";
    
    int z = 1;
    it = n.begin();
    for (; it < n.end(); it++)
    {
        std::cout << "\n  " << z << ".\t";
        it -> printVertex();
        z++;
    }
}

void Edge::addEdgePair(Edge pair [2], std::vector<Edge> & vec, Vertex left, Vertex right)
{
    (pair) -> setUV(left, right);
    (pair + 1) -> setUV(right, left);
    vec.push_back(*pair);
    vec.push_back(*(pair + 1));
}

void Edge::printEdges(std::vector<Edge> vec)
{
    int c = 1;
    std::vector<Edge>::iterator it;
    for (it = vec.begin(); it < vec.end(); it++)
    {
        std::cout << "\n  " << c << ".\t";
        it -> printEdge();
        c++;
    }
}

void Vertex::printVertices(std::vector<Vertex> vec)
{
    int c = 1;
    std::vector<Vertex>::iterator it;
    for (it = vec.begin(); it < vec.end(); it++)
    {
        std::cout << c << ".\t";
        it -> printVertex();
        std::cout << "\n";
        c++;
    }
}

void Vertex::onboarding(int sourceArray [][2], int currentSize, int prevSize, int & edgeCount, Vertex * vertices, Edge * edges, std::vector<Vertex> & U, std::vector<Edge> & edgeVector, int e_SIZE)
{
    for (int p = 0; p < currentSize; p++)
    {
        (vertices + p) -> setXYfromArray(*(sourceArray + p));
        U.push_back(*(vertices + p));
        if (  (vertices + p) -> scanLeft(U).getX() >= 0 &&
              edgeCount <= e_SIZE)
        {
            Edge::addEdgePair(
                              (edges + edgeCount),
                              edgeVector,
                              *(vertices + p),
                              (vertices + p) -> scanLeft(U)  );
            edgeCount += 2;
        }
        if (  (vertices + p) -> scanDown(U).getX() >= 0 &&
              edgeCount <= e_SIZE)
        {
            Edge::addEdgePair(
                              (edges + edgeCount),
                              edgeVector,
                              *(vertices + p),
                              (vertices + p) -> scanDown(U)  );
            edgeCount += 2;
        }
    }
}

class Path
{
    private:
        Vertex * path;
        bool hasCoffee;
        int size;
        int capacity;
        bool pConsoleDetail;
    
    public:
        Path();
        Path(const Path &);
        ~Path();
    
    public:
        int getPathSize() const;
        Vertex * getPathPtr() const;
        bool getHasCoffee() const;
    
    public:
        Path operator=(const Path &);
    
    public:
        void verifyCapacity();

    public: // expand ex operation
        static void expandEx(Path, std::vector<Vertex> &);
    
    public: // frontier operations
        static void addToFrontier(Path, std::vector<Vertex> &);
        static void removeFromFrontier(Path, std::vector<Vertex> &);
    
    public:
        void addVertex(Vertex);
        int findVertexIndex(Vertex);
        static int findForwardNeighbours(std::vector<Edge>, std::vector<Vertex>, std::vector<Vertex>, std::vector<Vertex> &);
    
    public:
        void printPath();
    
    public:
        void showConsoleDetail();
};

Path::Path()
{
    this -> capacity = 15;
    this -> size = 0;
    this -> hasCoffee = false;
    this -> pConsoleDetail = false;
    
    this -> path = new Vertex [this -> capacity];

    if (this -> pConsoleDetail)
        std::cout << "\nDefault constructor for a Path object has run.";
}

Path::Path(const Path & right)
{
    this -> hasCoffee = right.hasCoffee;
    this -> size = right.size;
    this -> capacity = right.capacity;
    this -> pConsoleDetail = right.pConsoleDetail;
    
    this -> path = new Vertex[this -> capacity];
    if (right.size > 0)
        for (int i = 0; i < right.size; i++)
            *(this -> path + i) = *(right.path + i);
    
    if (this -> pConsoleDetail)
        std::cout << "\nCopy constructor for a Path object has run.";
}

Path::~Path()
{
    if (this -> pConsoleDetail)
        std::cout << "\nPath destructor will deallocate " << this -> path << ".";
    
    if (this -> path != nullptr)
    {
        delete [] this -> path;
        this -> path = nullptr;
    }
    
    if (this -> pConsoleDetail)
        std::cout << "\nDestructor for a Path object has run.";
}

int Path::getPathSize() const
{
    return this -> size;
}

Vertex * Path::getPathPtr() const
{
    return this -> path;
}

bool Path::getHasCoffee() const
{
    return this -> hasCoffee;
}

void Path::verifyCapacity()
{
    if (this -> size >= this -> capacity - 2)
    {
        this -> capacity *= 2;
        
        Vertex * newPath = new Vertex [this -> capacity];
        
        for (int i = 0; i < this -> size; i++)
            *(newPath + i) = *(this -> path + i);
        
        std::swap(this -> path, newPath);
        delete [] newPath;
        newPath = nullptr;
        
        std::cout << "\nPath capacity has increased to " << this -> capacity << ".";
    }
    else {
        std::cout << "\nPath capacity maintained at " << this -> capacity << ".";
    }
}

void Path::expandEx(Path newPath, std::vector<Vertex> & ex)
{
    std::vector<Vertex>::iterator itex;
    Vertex * path = newPath.getPathPtr();
    int newPathSize = newPath.getPathSize();
    for (int i = 0; i < newPathSize - 1; i++)
    {
        itex = std::find(ex.begin(), ex.end(), *(path + i));
        if (itex != ex.end())
            ex.push_back(*(path + i));
    }
}

void Path::addToFrontier(Path newPath, std::vector<Vertex> & fr)
{
    std::vector<Vertex>::iterator itfr;
    Vertex * path = newPath.getPathPtr();
    int position = newPath.getPathSize() - 1;
    itfr = std::find(fr.begin(), fr.end(), *(path + position));
    if (itfr != fr.end())
        fr.push_back(*(path + position));
}

void Path::removeFromFrontier(Path newPath, std::vector<Vertex> & fr)
{
    std::vector<Vertex>::iterator itfr;
    Vertex * path = newPath.getPathPtr();
    int newPathSize = newPath.getPathSize();
    for (int i = 0; i < newPathSize - 1; i++)
    {
        itfr = std::find(fr.begin(), fr.end(), *(path + i));
        if (itfr != fr.end())
            fr.erase(itfr);
    }
}

Path Path::operator=(const Path & right)
{
    if (this != & right)
    {
        if (this -> path)
            delete [] this -> path;
            
        this -> hasCoffee = right.hasCoffee;
        this -> size = right.size;
        this -> capacity = right.capacity;
        
        this -> path = new Vertex[this -> capacity];
        if (right.size > 0)
            for (int i = 0; i < this -> size; i++)
                *(this -> path + i) = *(right.path + i);
    }
    return * this;
}

void Path::addVertex(Vertex obj)
{
    int t = this -> size;
    this -> size++;
    verifyCapacity();
    
    *(this -> path + t) = obj;
    
    if (obj.getC() == true)
        this -> hasCoffee = true;
}

int Path::findVertexIndex(Vertex target)
{
    int t = this -> size;
    for (int i = 0; i < t; i++)
        if (target.getX() == (this -> path + i) -> getX())
            if (target.getY() == (this -> path + i) -> getY())
                return i;
    return -1;
}

int Path::findForwardNeighbours(std::vector<Edge> edgeVector, std::vector<Vertex> fr, std::vector<Vertex> ex, std::vector<Vertex> & n)
{
    n.clear();
    int rv = -1;
    
    std::vector<Vertex>::iterator itfr;
    itfr = fr.begin();
    for (; itfr < fr.end(); itfr++)
        Edge::findNeighbours(edgeVector, *itfr, n);
    
    std::vector<Vertex>::iterator itn;
    itn = n.begin();
    for (; itn < n.end(); itn++)
    {
        std::vector<Vertex>::iterator itex;
        itex = std::find(ex.begin(), ex.end(), *itn);
        if (itex != ex.end())
            n.erase(itn);
    }
    
    if (n.size() > 0)
        rv = (int) n.size();
    
    return rv;
}

void Path::printPath()
{
    std::cout << "\n{ ";
    if (this -> size > 0)
    {
        for (int i = 0; i < (this -> size - 1); i++)
        {
            (this -> path[i]).printVertex();
            std::cout << ", ";
        }
        (this -> path[(this -> size) - 1]).printVertex();
    } else {
        std::cout << "empty";
    }
    std::cout << " }";
}

void Path::showConsoleDetail()
{
    this -> pConsoleDetail = true;
}

class PathBook
{
    public:
        Vertex start;
        Path * book;
        int bookSize;
        int bookCapacity;
        int pathSize;
        bool pbConsoleDetail;
    
    public:
        PathBook();
        PathBook(Vertex);
        PathBook(const PathBook &);
        PathBook(std::vector<Vertex>, std::vector<Vertex>, std::vector<Vertex> &, const PathBook &, int, std::vector<Edge>);
        ~PathBook();

    public:
        Path * getBookPtr() const;
        int getBookSize() const;
    
    public:
        void setPathSize();
        void showConsoleDetail();
    
    public:
        PathBook operator=(const PathBook &);
    
    public:
        int findCoffee() const;
    
    public:
        void addPathToBook(Path);
        void resizeBook();
        int findPath(Path);
        void initiatePaths(std::vector<Vertex> &, std::vector<Edge>);
        void extendFromVertex(Path, std::vector<Vertex> &, std::vector<Vertex> &, std::vector<Vertex> &, std::vector<Edge>);
        void printBook();
};

PathBook::PathBook()
{
    this -> bookSize = 0;
    this -> bookCapacity = 10;
    this -> book = new Path[this -> bookCapacity];
    this -> pbConsoleDetail = false;
    
    if (this -> pbConsoleDetail)
        std::cout << "\nPathBook default constructor has run.";
}

PathBook::PathBook(Vertex x)
{
    this -> start = x;
    this -> bookSize = 0;
    this -> bookCapacity = 10;
    this -> book = new Path[this -> bookCapacity];
    this -> pbConsoleDetail = false;
    
    if (this -> pbConsoleDetail)
        std::cout << "\nPathBook 1 arg constructor has run.";
}

PathBook::PathBook(const PathBook & right)
{
    this -> start = right.start;
    this -> bookSize = right.bookSize;
    this -> bookCapacity = right.bookCapacity;
    this -> pbConsoleDetail = right.pbConsoleDetail;
    this -> book = new Path[right.bookCapacity];
    
    if (right.bookSize > 0)
        for (int i = 0; i < right.bookSize; i++)
            *(this -> book + i) = *(right.book + i);
    
    if (this -> pbConsoleDetail)
        std::cout << "\nPathBook copy constructor has run.";
}

PathBook::PathBook(std::vector<Vertex> fr, std::vector<Vertex> ex, std::vector<Vertex> & n, const PathBook & startPathBookObj, int targetPathSize, std::vector<Edge> edgeVector)
{
    int checksum = 0;
    Path * startPathPtr = startPathBookObj.getBookPtr();
    int startPathSize = startPathBookObj.getBookSize();
    for (int i = 0; i < startPathSize; i++)
        if ((startPathPtr + i) -> getPathSize() != targetPathSize)
            checksum--;
    if (startPathBookObj.bookSize < 1)
        checksum--;
    int bSize = 0;
    if (checksum != 0)
    {
        this -> bookSize = 0;
        this -> bookCapacity = 10;
        this -> book = new Path[this -> bookCapacity];
        this -> pbConsoleDetail = false;

        std::cout << "\nPathBook 6 arg constructor cannot run.";
        std::cout << "\nPathBook default constructor has run.";
    }
    else
    {
        this -> start = startPathBookObj.start;
        this -> bookCapacity = 3 * (startPathBookObj.bookSize);
        this -> book = new Path[this -> bookCapacity];
        this -> bookSize = 0;
        this -> pbConsoleDetail = false;
        
        for (int k = 0; k < startPathSize; k++)
        {
            n.clear();
            extendFromVertex(*(startPathPtr + k), fr, ex, n, edgeVector);
            bSize += n.size();
        }
        this -> bookSize = bSize;

        std::cout << "\nPathBook 6 arg constructor has run.";
    }
}

PathBook::~PathBook()
{
    if (this -> pbConsoleDetail)
        std::cout << "\nPathBook destructor will deallocate " << this -> book << ".";
    if (this -> book != nullptr)
    {
        delete [] this -> book;
        this -> book = nullptr;
    }
    if (this -> pbConsoleDetail)
        std::cout << "\nPathBook destructor has run.";
}

Path * PathBook::getBookPtr() const
{
    return this -> book;
}

int PathBook::getBookSize() const
{
    return this -> bookSize;
}

void PathBook::setPathSize()
{
    int size = (this -> book + this -> bookSize) -> getPathSize();
    this -> pathSize = size;
}

void PathBook::showConsoleDetail()
{
    this -> pbConsoleDetail = true;
}

PathBook PathBook::operator=(const PathBook & right)
{
    if (this != & right)
    {
        if (this -> book)
            delete [] this -> book;
            
        this -> start = right.start;
        this -> bookSize = right.bookSize;
        this -> bookCapacity = right.bookCapacity;
        this -> book = new Path[right.bookCapacity];
        
        if (right.bookSize > 0)
            for (int i = 0; i < right.bookSize; i++)
                *(this -> book + i) = *(right.getBookPtr() + i);
    }
    return * this;
}

int PathBook::findCoffee() const
{
    Path * start = this -> book;
    for (int i = 0; i < this -> bookSize; i++)
        if (  (start + i) -> getHasCoffee()  )
            return i;
    return -1;
}

void PathBook::addPathToBook(Path x)
{
    *(this -> book + this -> bookSize) = x;
    this -> bookSize++;
    resizeBook();
}

void PathBook::resizeBook()
{
    if (this -> bookSize > (this -> bookCapacity - 1))
    {
        this -> bookCapacity *= 2;
        
        Path * newBook = new Path [this -> bookCapacity];
        for (int i = 0; i < this -> bookSize; i++)
            *(newBook + i) = *(this -> book + i);
        
        std::swap(this -> book, newBook);
        delete [] newBook;
        newBook = nullptr;
        
        std::cout << "\nPathBook object capacity increased to " << this -> bookCapacity << ".";
    }
    else if (this -> bookSize < (this -> bookCapacity / 3) &&
             this -> bookCapacity > 400)
    {
        this -> bookCapacity /= 2;
        
        Path * newBook = new Path [this -> bookCapacity];
        for (int i = 0; i < this -> bookSize; i++)
            *(newBook + i) = *(this -> book + i);
        std::cout << "\nOld PathBook object address: " << this -> book << ".";
        
        std::swap(this -> book, newBook);
        delete [] newBook;
        newBook = nullptr;
        
        std::cout << "\nPathBook object capacity decreased to " << this -> bookCapacity << ".";
        std::cout << "\nNew PathBook object address: " << this -> book << ".";
    }
    else
    {
        std::cout << "\nPathBook object capacity maintained at " << this -> bookCapacity << ".";
    }
}

int PathBook::findPath(Path x)
{
    int m = 0;
    Vertex * target = x.getPathPtr();
    if (this -> bookSize > 0)
        for (int i = 0; i < this -> bookSize; i++)
        {
            int pathSize = (this -> book + i) -> getPathSize();
            Vertex * v = (this -> book + i) -> getPathPtr();
            m -= pathSize;
            for (int j = 0; j < pathSize; j++)
                if (target -> getX() == (v + j) -> getX())
                    if (target -> getY() == (v + j) -> getY())
                        m++;
            if (m == 0)
                return i;
        }
    return -1;
}

void PathBook::initiatePaths(std::vector<Vertex> & n, std::vector<Edge> edgeVector)
{
    std::vector<Vertex>::iterator itn;
    n.clear();
    int test = (Edge::findNeighbours(edgeVector, this -> start, n)).getX();
    if (test >= 0)
    {
        itn = n.begin();
        for (; itn < n.end(); itn++)
        {
            Path * next = new Path;
            next -> addVertex(this -> start);
            next -> addVertex(*itn);
            if (findPath(*next) < 0)
            {
                addPathToBook(*next);
                std::cout << "\nMethod initiatePaths has added a path.";
            }
            delete next;
            next = nullptr;
        }
    }
}

void PathBook::extendFromVertex(Path startPath, std::vector<Vertex> & fr,std::vector<Vertex> & ex, std::vector<Vertex> & n, std::vector<Edge> edgeVector)
{
    std::vector<Vertex>::iterator itn;
    std::vector<Vertex>::iterator itex;
    n.clear();
    Vertex pivot = *(startPath.getPathPtr() + startPath.getPathSize() - 1);
    std::cout << "\nPath object startPath: ";
    startPath.printPath();
    std::cout << "\nPath object startPath path size: ";
    std::cout << startPath.getPathSize();
    Edge::findNeighbours(edgeVector, pivot, n).getX();
    int test = (int) n.size();
    std::cout << "\nTest value: " << test;
    for (itn = n.end() - 1; itn >= n.begin(); itn--)
    {
        itex = std::find(ex.begin(), ex.end(), *itn);
        if (itex != ex.end())
        {
            n.erase(itn);
            test--;
        }
    }
    if (test >= 0)
    {
        itn = n.begin();
        for (; itn < n.end(); itn++)
        {
            Path * next = new Path;
            *next = startPath;
            std::cout << "\nNew path: ";
            next -> printPath();
            std::cout << "\nVertex to add: ";
            itn -> printVertex();
            next -> addVertex(*itn);
            if (findPath(*next) < 0)
            {
                addPathToBook(*next);
                std::cout << "\nMethod extendFromVertex has added a path.";
            }
            delete next;
            next = nullptr;
        }
    }
}

void PathBook::printBook()
{
    if (this -> bookSize == 0)
        std::cout << "\nThe PathBook object has zero paths.";
    else {
        int n = 1;
        for (int c = 0; c < this -> bookSize; c++)
        {
            std::cout << "\nPath " << n << ":";
            (this -> book + c) -> printPath();
            n++;
        }
    }
}

void Edge::makeEdgesAndVertices(std::vector<Vertex> & U, Vertex * vertices, std::vector<Edge> & edgeVector, Edge * edges, int e_SIZE, int v_SIZE)
{
    const int c0_SIZE = 6;
    const int c1_SIZE = 2;
    const int c2_SIZE = 5;
    const int c3_SIZE = 5;
    const int c4_SIZE = 5;
    const int c5_SIZE = 4;
    const int c6_SIZE = 6;
    const int c7_SIZE = 6;
    const int c8_SIZE = 6;
    int edgeCount = 0;
    
// COLUMN 0
    
    int c0_Array [c0_SIZE][2]  = { {0,0}, {0,1}, {0,2}, \
                                   {0,3}, {0,4}, {0,5} };
   
    (vertices) -> placeC();
    
    Vertex::onboarding(  c0_Array,
                         c0_SIZE,
                         0,
                         edgeCount,
                         vertices,
                         edges,
                         U,
                         edgeVector,
                         e_SIZE      );
    
// COLUMN 1
    
    int c1_Array [c1_SIZE][2]  = { {1,0}, {1,5} };
    
    Vertex::onboarding(  c1_Array,
                         c1_SIZE,
                         c0_SIZE,
                         edgeCount,
                         (vertices + c0_SIZE),
                         edges,
                         U,
                         edgeVector,
                         e_SIZE      );
    
// COLUMN 2
    
    int c2_Array [c2_SIZE][2]  = { {2,0}, {2,1}, {2,2}, \
                                   {2,4}, {2,5} };
    
    Vertex::onboarding(  c2_Array,
                         c2_SIZE,
                         (c0_SIZE + c1_SIZE),
                         edgeCount,
                         (vertices + c0_SIZE + c1_SIZE),
                         edges,
                         U,
                         edgeVector,
                         e_SIZE      );
    
// COLUMN 3
    
    int c3_Array [c3_SIZE][2]  = { {3,0}, {3,1}, {3,2}, \
                                   {3,4}, {3,5} };
  
    Vertex::onboarding(  c3_Array,
                         c3_SIZE,
                         (c0_SIZE + c1_SIZE + c2_SIZE),
                         edgeCount,
                         (vertices + c0_SIZE + c1_SIZE + c2_SIZE),
                         edges,
                         U,
                         edgeVector,
                         e_SIZE      );
    
// COLUMN 4
    
    int c4_Array [c4_SIZE][2]  = { {4,0}, {4,1}, {4,2}, \
                                   {4,4}, {4,5} };
    
    (vertices + c0_SIZE + c1_SIZE + c2_SIZE + c3_SIZE) -> placeC();
    
    Vertex::onboarding(  c4_Array,
                         c4_SIZE,
                         (c0_SIZE + c1_SIZE + c2_SIZE + c3_SIZE),
                         edgeCount,
                         (vertices + c0_SIZE + c1_SIZE + c2_SIZE + c3_SIZE),
                         edges,
                         U,
                         edgeVector,
                         e_SIZE      );
    
// COLUMN 5
    
    int c5_Array [c5_SIZE][2]  = { {5,0}, {5,1}, {5,2}, \
                                   {5,5} };
    
    Vertex::onboarding(  c5_Array,
                         c5_SIZE,
                         (c0_SIZE + c1_SIZE + c2_SIZE + c3_SIZE + c4_SIZE),
                         edgeCount,
                         (vertices + c0_SIZE + c1_SIZE + c2_SIZE + c3_SIZE + c4_SIZE),
                         edges,
                         U,
                         edgeVector,
                         e_SIZE      );

// COLUMN 6
    
    int c6_Array [c6_SIZE][2]  = { {6,0}, {6,1}, {6,2}, \
                                   {6,3}, {6,4}, {6,5} };

    Vertex::onboarding(  c6_Array,
                         c6_SIZE,
                         (c0_SIZE + c1_SIZE + c2_SIZE + c3_SIZE + c4_SIZE + c5_SIZE),
                         edgeCount,
                         (vertices + c0_SIZE + c1_SIZE + c2_SIZE + c3_SIZE + c4_SIZE + c5_SIZE),
                         edges,
                         U,
                         edgeVector,
                         e_SIZE      );
    
// COLUMN 7
    
    int c7_Array [c7_SIZE][2]  = { {7,0}, {7,1}, {7,2}, \
                                   {7,3}, {7,4}, {7,5} };
    
    (vertices + c0_SIZE + c1_SIZE + c2_SIZE + c3_SIZE + c4_SIZE + c5_SIZE + c6_SIZE + 4) -> placeC();
    
    Vertex::onboarding(  c7_Array,
                         c7_SIZE,
                         (c0_SIZE + c1_SIZE + c2_SIZE + c3_SIZE + c4_SIZE + c5_SIZE + c6_SIZE),
                         edgeCount,
                         (vertices + c0_SIZE + c1_SIZE + c2_SIZE + c3_SIZE + c4_SIZE + c5_SIZE + c6_SIZE),
                         edges,
                         U,
                         edgeVector,
                         e_SIZE      );
    
// COLUMN 8
    
    int c8_Array [c8_SIZE][2]  = { {8,0}, {8,1}, {8,2}, \
                                   {8,3}, {8,4}, {8,5} };
    
    Vertex::onboarding(  c8_Array,
                         c8_SIZE,
                         (c0_SIZE + c1_SIZE + c2_SIZE + c3_SIZE + c4_SIZE + c5_SIZE + c6_SIZE + c7_SIZE),
                         edgeCount,
                         (vertices + c0_SIZE + c1_SIZE + c2_SIZE + c3_SIZE + c4_SIZE + c5_SIZE + c6_SIZE + c7_SIZE),
                         edges,
                         U,
                         edgeVector,
                         e_SIZE      );
    
// CONSOLE OUTPUT
    
    std::cout << "\n";
    Vertex::printVertices(U);
    std::cout << "Result of search for (1,0):  ";
    Vertex::findVertex(1,0,U).printVertex();
    std::cout << "\nResult of search for (10,10):  ";
    Vertex::findVertex(10,10,U).printVertex();
    
    std::vector<Vertex>::iterator itp;
    itp = U.begin();
    for (; itp < U.end(); itp ++)
        itp -> printNeighbours(edgeVector);
    std::cout << "\nAll edges:";
    Edge::printEdges(edgeVector);
}

class WorkBook
{
    public:
        PathBook * books;
        Vertex start;
        Vertex goal;
        int booksCount;
        int booksBuffer;
        int pathSizeTarget;
        int solution;
        std::vector<Vertex> U;
        std::vector<Vertex> n;
        std::vector<Vertex> ex;
        std::vector<Vertex> fr;
        std::vector<Edge> edgeVector;
    
    public:
        WorkBook();
        WorkBook(int);
        WorkBook(const WorkBook &);
        WorkBook(int, std::vector<Vertex> &, std::vector<Vertex> &, std::vector<Vertex> &, std::vector<Vertex> &, std::vector<Edge> &);
        ~WorkBook();
    
    public:
        int getPathSizeTarget() const;
    
    public:
        void addBook();
        void addBooks(int);
        void calibrate(int);
    
    public:
        void printBooks();
        void printEx();
        void printFr();
        void printGoal();
        void printN();
        void printSolution();
        void printStart();
        void printU();

    public:
        bool goalFound();
};

WorkBook::WorkBook()
{
    this -> booksCount = 0;
    this -> booksBuffer = 25;
    this -> pathSizeTarget = 2;
    
    this -> books = new PathBook [this -> booksBuffer];
    
    std::cout << "\nWorkBook default constructor has run.";
}

WorkBook::WorkBook(int n)
{
    this -> booksCount = 0;
    this -> booksBuffer = 25;
    this -> pathSizeTarget = n;
    
    this -> books = new PathBook [this -> booksBuffer];
    
    std::cout << "\nWorkBook 1 arg constructor has run.";
}

WorkBook::WorkBook(const WorkBook & right)
{
    this -> booksCount = right.booksCount;
    this -> booksBuffer = right.booksBuffer;
    this -> pathSizeTarget = right.pathSizeTarget;
    
    this -> books = new PathBook [this -> booksBuffer];
    if (right.booksCount > 0)
        for (int i = 0; i < right.booksCount; i++)
            *(this -> books + i) = *(right.books + i);
    
    this -> start = right.start;
    this -> goal = right.goal;
    
    this -> U = right.U;
    this -> n = right.n;
    this -> ex = right.ex;
    this -> fr = right.fr;
    this -> edgeVector = right.edgeVector;
    
    std::cout << "\nWorkBook copy constructor has run.";
}

WorkBook::WorkBook(int p,
                   std::vector<Vertex> & universe,
                   std::vector<Vertex> & neighbours,
                   std::vector<Vertex> & exFrontier,
                   std::vector<Vertex> & frontier,
                   std::vector<Edge> & edgeVec)
{
    const int v_SIZE = 45;
    const int e_SIZE = 130;
    
    Vertex * vertices = new Vertex[v_SIZE];
    Edge * edges = new Edge[e_SIZE];

    Edge::makeEdgesAndVertices(universe, vertices, edgeVec, edges, e_SIZE, v_SIZE);
    
    this -> booksCount = 1;
    this -> booksBuffer = 25;
    this -> pathSizeTarget = p;
    this -> books = new PathBook [this -> booksBuffer];
    this -> U = universe;
    this -> n = neighbours;
    this -> ex = exFrontier;
    this -> fr = frontier;
    this -> edgeVector = edgeVec;
    
    std::vector<Vertex>::iterator itu = (this -> U).begin();
    itu += 15;
    this -> start = *itu;
    itu++;
    this -> goal = *itu;
    *(this -> books) = PathBook(this -> start);
    (this -> books) -> initiatePaths(this -> n, this -> edgeVector);
    
    std::cout << "\nWorkBook 6 arg constructor has run.";
    
    delete [] vertices;
    vertices = nullptr;
    
    delete [] edges;
    edges = nullptr;
}

WorkBook::~WorkBook()
{
    std::cout << "\nWorkBook destructor will deallocate " << this -> books << ".";
    if (this -> books != nullptr)
    {
        delete [] this -> books;
        this -> books = nullptr;
    }
    
    std::cout << "\nWorkBook destructor has run.";
}

int WorkBook::getPathSizeTarget() const
{
    return this -> pathSizeTarget;
}

void WorkBook::addBook()
{
    if (this -> booksCount < this -> booksBuffer - 1)
    {
        this -> booksCount++;
        *(this -> books + this -> booksCount - 1) = PathBook(this -> fr, this -> ex, this -> n, *(this -> books + this -> booksCount - 2), pathSizeTarget, this -> edgeVector);
        this -> pathSizeTarget++;
        
        std::cout << "\nWorkBook addBook method has run.";
        std::cout << "\nWorkBook booksCount is now " << this -> booksCount << ".";
    }
}

void WorkBook::addBooks(int n)
{
    int m = 25;
    bool guard = false;
    while (m > 0 && guard == false && (this -> books + this -> booksCount - 1) -> getBookSize() > 0)
    {
        calibrate(n);
        addBook();
        m--;
        guard = goalFound();
    }
    printBooks();
}

// update exFrontier and frontier vectors
// delay the advance of exFrontier by increasing n

void WorkBook::calibrate(int n)
{
    (this -> ex).clear();
    std::vector<Vertex>::iterator itex;
    (this -> fr).clear();
    std::vector<Vertex>::iterator itfr;

    PathBook * lastBook = this -> books + this -> booksCount - 1;
    int lastBookSize = lastBook -> getBookSize();
    Vertex * target;
    int targetSize;
    
    for (int i = 0; i < lastBookSize; i++)
    {
        target = (lastBook -> getBookPtr() + i) -> getPathPtr();
        targetSize = (lastBook -> getBookPtr() + i) -> getPathSize();
        for (int j = 0; j < targetSize - n; j++)
        {
            itex = ex.begin();
            itex = std::find(ex.begin(), ex.end(), *(target + j));
            if (itex == ex.end())
                ex.push_back(*(target + j));
        }
        itfr = std::find(fr.begin(), fr.end(), *(target - 1));
        if (itfr == fr.end())
            fr.push_back(*(target + targetSize - 1));
    }
}

void WorkBook::printBooks()
{
    int m = 1;
    for (int i = 0; i < this -> booksCount; i++)
    {
        std::cout << "\nWORKBOOK " << m << ":";
        (this -> books + i) -> printBook();
        m++;
    }
}

void WorkBook::printEx()
{
    std::cout << "\nVector ex contains:";
    int m = 1;
    if ((this -> ex).size() > 0)
    {
        std::vector<Vertex>::iterator itex;
        itex = (this -> ex).begin();
        for (; itex < (this -> ex).end(); itex++)
        {
            std::cout << "\n   " << m << "\t";
            itex -> printVertex();
            m++;
        }
    } else
        std::cout << "\nVector ex is empty.";
}

void WorkBook::printFr()
{
    std::cout << "\nVector fr contains:";
    int m = 1;
    if ((this -> fr).size() > 0)
    {
        std::vector<Vertex>::iterator itfr;
        itfr = (this -> fr).begin();
        for (; itfr < (this -> fr).end(); itfr++)
        {
            std::cout << "\n   " << m << "\t";
            itfr -> printVertex();
            m++;
        }
    } else
        std::cout << "\nVector fr is empty.";
}

void WorkBook::printGoal()
{
    std::cout << "\nWorkBook object goal attribute: ";
    (this -> goal). printVertex();
}

void WorkBook::printN()
{
    std::cout << "\nVector n contains:";
    int m = 1;
    if ((this -> n).size() > 0)
    {
        std::vector<Vertex>::iterator itn;
        itn = (this -> n).begin();
        for (; itn < (this -> n).end(); itn++)
        {
            std::cout << "\n   " << m << "\t";
            itn -> printVertex();
            m++;
        }
    } else
        std::cout << "\nVector n is empty.";
}

void WorkBook::printSolution()
{
    if (this -> solution)
    {
        int targetIndex = this -> solution;
        std::cout << "\nSolution found:";
        ((this -> books + this -> booksCount - 1) -> getBookPtr() + targetIndex) -> printPath();
    } else
        std::cout << "\nNo solution found.";
}

void WorkBook::printStart()
{
    std::cout << "\nWorkBook object start attribute: ";
    (this -> start). printVertex();
}

void WorkBook::printU()
{
    std::cout << "\nVector U contains:";
    int m = 1;
    if ((this -> U).size() > 0)
    {
        std::vector<Vertex>::iterator itu;
        itu = (this -> U).begin();
        for (; itu < (this -> U).end(); itu++)
        {
            std::cout << "\n   " << m << "\t";
            itu -> printVertex();
            m++;
        }
    } else
        std::cout << "\nVector U is empty.";
}

bool WorkBook::goalFound()
{
    bool rv = false;
    
    PathBook * lastBook = this -> books + this -> booksCount - 1;
    int lastBookSize = lastBook -> getBookSize();
    int targetIndex = -1;

    for (int i = 0; i < lastBookSize; i++)
        if ((lastBook -> getBookPtr() + i) -> getHasCoffee())
            if ((lastBook -> getBookPtr() + i) -> findVertexIndex(this -> goal) > -1)
                targetIndex = i;
    
    if (targetIndex > -1)
    {
        std::cout << "\nGoal found:";
        (lastBook -> getBookPtr() + targetIndex) -> printPath();
        rv = true;
        this -> solution = targetIndex;
    } else
        std::cout << "\nGoal not found.";
    
    return rv;
}

void runWorkBook()
{
    std::cout << "Testing will start.";
    std::vector<Vertex> U;
    std::vector<Vertex> n;
    std::vector<Vertex> ex;
    std::vector<Vertex> fr;
    std::vector<Edge> edgeVector;
    
    const int DELAY = 2;
    
    WorkBook wb ( 2, // initial path size target
                  U,
                  n,
                  ex,
                  fr,
                  edgeVector );
    
    wb.addBooks ( DELAY );
    
    std::cout << "\nThe current path size target is " << wb.getPathSizeTarget() << ".";
    
    wb.printU();
    wb.printSolution();
}

#endif /* graphSolution_h */
