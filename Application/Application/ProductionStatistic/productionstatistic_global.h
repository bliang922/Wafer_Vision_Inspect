#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(PRODUCTIONSTATISTIC_LIB)
#  define PRODUCTIONSTATISTIC_EXPORT Q_DECL_EXPORT
# else
#  define PRODUCTIONSTATISTIC_EXPORT Q_DECL_IMPORT
# endif
#else
# define PRODUCTIONSTATISTIC_EXPORT
#endif
