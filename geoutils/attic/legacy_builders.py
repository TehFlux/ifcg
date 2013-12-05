# Builders that are not used anymore but may be useful some time.

def buildClassXMLIO(source, target, env):
    """Builder function to build XML I/O header and implementation file 
       fragments from class configuration."""
    classNames = []
    for it in source:
        cn, ext = os.path.splitext(os.path.basename(it.path))
        if (ext == '.conf'):
            classNames += [cn]
    # Figure out the template module and output file suffix to be used.
    templateModule = "unknown"
    suffix = ".none"
    cn, ext = os.path.splitext(os.path.basename(target[0].path))
    if (ext == '.cpp'):
        templateModule = "xml.impl.xmlutils_fragment"
        suffix = "_xml.cpp"
    elif (ext == '.hpp'):
        if (cn.endswith("_xml")):
            templateModule = "xml.header.xmlutils_fragment"
            suffix = "_xml.hpp"
        elif (cn.endswith("_xml_private")):
            templateModule = "xml.header.xmlutils_fragment_private"
            suffix = "_xml_private.hpp"
    for cn in classNames:
        c0 = ("iftpl0 -I " + lc.ifobjectTemplatePath 
            + " " + templateModule + " conf/class/" 
                + cn + ".conf conf/main.conf")
        print c0
        f0 = open("temp/xmlutils/" + cn + suffix, 'w')
        sp0 = subprocess.call(shlex.split(c0), stdout = f0)
        f0.close()

def buildXMLIO(source, target, env):
    """Builder function to build XML I/O header and implementation 
       files from class XML I/O file fragments."""
    classNames = []
    suffix = ".none"
    for it in source:
        cn, ext = os.path.splitext(os.path.basename(it.path))
        if (((ext == '.hpp')
            or (ext == '.cpp'))):
            if (cn.endswith("_xml")): 
                classNames += [ cn[:-4] ]
            elif (cn.endswith("_xml_private")):
                classNames += [ cn[:-12] ]
        elif (ext == '.tpl'):
            templateFile = it.path
        if (suffix == ".none"):
            # Figure out the suffix for the source files.
            if (ext == '.cpp'):
                suffix = "_xml.cpp"
            elif (ext == '.hpp'):
                if (cn.endswith("_xml")):
                    suffix = "_xml.hpp"
                elif (cn.endswith("_xml_private")):
                    suffix = "_xml_private.hpp"
    p0 = re.compile("/\*.*?\*/", re.DOTALL)
    tplData = {}
    for cn in classNames:
        tplData[cn] = p0.sub('', open('temp/xmlutils/' + cn 
            + suffix).read())
    tplStr = open(templateFile).read()
    tpl = string.Template(tplStr)
    for it in target:
        f0 = open(it.path, 'w')
        f0.write(tpl.substitute(tplData))
        f0.close()


