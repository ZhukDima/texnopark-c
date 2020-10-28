#include "gtest/gtest.h"
#include <dirent.h>
#include <glib-2.0/glib.h>

extern "C"
{
#include "testy/TF-IDFMetric.h"
}

//All right
TEST(findTFIDFMetric1, ok)
{
    printTopFiveTFIDFMetric("../../test/testFiles");
}
