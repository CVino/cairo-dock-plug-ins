
########### sources ###############

SET(cd-Doncky_LIB_SRCS
	applet-init.c 		applet-init.h
	applet-config.c 		applet-config.h
	applet-notifications.c 	applet-notifications.h
	applet-draw.c 		applet-draw.h
	applet-xml.c 		applet-xml.h
	applet-cpusage.c 		applet-cpusage.h
	applet-rame.c 		applet-rame.h
	applet-nvidia.c 		applet-nvidia.h
	applet-disk-usage.c 	applet-disk-usage.h
	applet-struct.h
)

add_library(${PACKAGE_DONCKY} SHARED ${cd-Doncky_LIB_SRCS})

########### compil ###############
add_definitions (-DMY_APPLET_SHARE_DATA_DIR="${donckydatadir}")
add_definitions (-DMY_APPLET_PREVIEW_FILE="preview.jpg")
add_definitions (-DMY_APPLET_CONF_FILE="Doncky.conf")
add_definitions (-DMY_APPLET_USER_DATA_DIR="Doncky")
add_definitions (-DMY_APPLET_VERSION="${VERSION_DONCKY}")
add_definitions (-DMY_APPLET_GETTEXT_DOMAIN="${GETTEXT_DONCKY}")
add_definitions (-DMY_APPLET_DOCK_VERSION="${dock_version}")
add_definitions (-DMY_APPLET_ICON_FILE="icon.png")
add_definitions (-DCD_APPLET_MULTI_INSTANCE="1")

include_directories (
	${PACKAGE_INCLUDE_DIRS})

link_directories (
	${PACKAGE_LIBRARY_DIRS})

target_link_libraries (${PACKAGE_DONCKY}
	${PACKAGE_LIBRARIES})

########### install files ###############

install(TARGETS ${PACKAGE_DONCKY} DESTINATION ${pluginsdir})




#original Makefile.am contents follow:

# #dnl Process this file with automake to produce Makefile.in
#
#lib_LTLIBRARIES = 
#	libcd-Doncky.la
#
#
#libcd_Doncky_la_SOURCES = 
#	applet-init.c
#	applet-init.h
#	applet-config.c
#	applet-config.h
#	applet-notifications.c
#	applet-notifications.h
#	applet-draw.c
#	applet-draw.h
#	applet-xml.c
#	applet-xml.h
#	applet-cpusage.c
#	applet-cpusage.h
#	applet-monitor.c
#	applet-monitor.h
#	applet-rame.c
#	applet-rame.h
#	applet-nvidia.c
#	applet-nvidia.h
#	applet-top.c
#	applet-top.h
#	applet-disk-usage.c
#	applet-disk-usage.h
#	applet-struct.h
#
#
#dock_version = `pkg-config --modversion cairo-dock`
#
#libcd_Doncky_la_CFLAGS = 
#	-I$(top_srcdir)/src
#	$(PACKAGE_CFLAGS)
#	-DMY_APPLET_SHARE_DATA_DIR=""${donckydatadir)""
#	-DMY_APPLET_PREVIEW_FILE=""preview.jpg""
#	-DMY_APPLET_CONF_FILE=""Doncky.conf""
#	-DMY_APPLET_USER_DATA_DIR=""Doncky""
#	-DMY_APPLET_VERSION=""${VERSION_DONCKY)""
#	-DMY_APPLET_GETTEXT_DOMAIN=""${GETTEXT_DONCKY)""
#	-DMY_APPLET_DOCK_VERSION=""${dock_version)""
#	-DMY_APPLET_ICON_FILE=""icon.png""
#	-DCD_APPLET_MULTI_INSTANCE="1"
#	-std=c99
#	-Werror-implicit-function-declaration
##	-g -ggdb -W -Wall
#
#
#libcd_Doncky_la_LIBADD = 
#	$(PACKAGE_LIBS) -lm
#
#
#libcd_Doncky_la_LDFLAGS =
#	-avoid-version -module
