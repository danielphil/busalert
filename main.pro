TEMPLATE = subdirs

SUBDIRS += \
    busalert \
    tests \
    buslib

# Dependency tip from https://vilimpoc.org/blog/2014/02/21/qmake-subdirs-project-automatic-dependencies/
# Not entirely sure if this is right, but the project seems to be happily building from clean
# now with this here.

buslib.subdir = buslib

tests.depends = buslib
busalert.depends = buslib
