#!/usr/bin/env python
# -*- coding: utf-8 -*-
import IFObjectBase as ib
import IFMapping as im

testName = "Matrix"
enableMemDebug = False

print("IFMapping test: %s" % testName)

# memory management
mm = ib.IFObject()
if (enableMemDebug):
    mmh = ib.IFMMEventHandler.getInstance()
    mmh.setLogFileName('temp/memdebug.log')
    mmh.clearLogFile()

m0 = im.Matrix.create(3, 3, 
    1., 200., 3., 
    40., 15.32, -1.61, 
    2., -0.621, 0.002)
mm.addLocalRef(m0)

m1 = im.Matrix.create(3, 2)
mm.addLocalRef(m1)

print("Matrix data (0):")
print(m0.getValueStringFormatted(3, 8))

m0.sampleColumns(2, m1)

print("Matrix data (1):")
print(m1.getValueStringFormatted(3, 8))

if (enableMemDebug):
    mm.removeAllLocalRefs()
    ib.IFMMEventHandler.cleanup()

print("All done!")
