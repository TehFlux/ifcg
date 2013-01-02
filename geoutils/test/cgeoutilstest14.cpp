#include <cmath>
#include <sstream>
#include <iomanip>
#include "geoutils/geoutils.hpp"
#include "geoutils/altjirageoutils.hpp"

using namespace std;
using namespace Ionflux::GeoUtils;
using namespace Ionflux::GeoUtils::TransformNodes;

int main(int argc, char** argv)
{
    cout << "Testing transform graph..." << endl;
    cout << "  Creating nodes..." << endl;
    
    LoadSVG* n0 = LoadSVG::create();
    n0->setFileName("test/images/leaf01.svg");
    n0->addElementID("leaf01");
    
    Center* n1 = Center::create();
    n1->setMethod(CENTER_BOUNDS);
    
    Normalize* n2 = Normalize::create();
    
    Scale* n3 = Scale::create();
    n3->setScale(Vector3(600., -600., 1.));
    
    Rotate* n4 = Rotate::create();
    n4->setAngle(0.25 * M_PI);
    
    WriteSVG* n5 = WriteSVG::create();
    n5->setFileName("temp/nodes02x.svg");
    
    TransformNodeVector v0;
    v0.push_back(n0);
    v0.push_back(n1);
    v0.push_back(n2);
    v0.push_back(n3);
    v0.push_back(n4);
    v0.push_back(n5);
    
    ostringstream s0;
    unsigned int i = 0;
    for (TransformNodeVector::iterator it = v0.begin(); 
        it != v0.end(); it++)
    {
        s0.str("");
        s0 << "n" << setfill('0') << setw(2);
        (*it)->setID(s0.str());
        i++;
    }
    
    cout << "  Creating graph..." << endl;
    
    TransformGraph g0;
    g0.addNodes(v0);
    g0.chain();
    g0.setIO();
    g0.update();
    
    cout << "    " << g0 << endl;
    cout << "    Nodes:" << endl;
    for (unsigned int i = 0; i < g0.getNumNodes(); i++)
        cout << "      " << *g0.getNode(i) << endl;
    cout << "    Connections:" << endl;
    for (unsigned int i = 0; i < g0.getNumNodes(); i++)
        cout << "      " << *g0.getNode(i) << endl;
    
    cout << "All done!" << endl;
    
    return 0;
}
