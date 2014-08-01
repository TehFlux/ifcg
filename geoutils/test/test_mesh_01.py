import IFObjectBase as ib
import CGeoUtils as cg
import math as m

testName = "Mesh #1: Tri-mesh"

print("CGeoUtils test: %s" % testName)

# memory management
mm = ib.IFObject()

# register XML object factories
cg.Vector2.getXMLObjectFactory()
cg.Vector3.getXMLObjectFactory()
cg.FaceData.getXMLObjectFactory()

inFile0 = 'temp/colorplane01.xml'
outFile0 = 'temp/colorplane-tri-01.xml'

m0 = cg.Mesh.create()

print("  Loading mesh from file '%s'..." % inFile0)

m0.loadFromXMLFile(inFile0)
m0.update()

if (m0.isTriMesh()):
    print("  Mesh already is a tri-mesh, nothing to be done.")
else:
    print("  Creating tri-mesh...")
    m0.makeTris()
    print("  Writing mesh to file '%s'..." % outFile0)
    m0.writeToXMLFile(outFile0)

print("All done!")
