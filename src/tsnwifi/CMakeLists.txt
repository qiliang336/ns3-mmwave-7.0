build_lib(
  LIBNAME tsnwifi
  SOURCE_FILES
    model/Sta-priority.cc
    model/switch-trace-application.cc
    helper/wifi-setup.cc
  HEADER_FILES
    model/Sta-priority.h
    model/switch-trace-application.h
    helper/wifi-setup.h
  LIBRARIES_TO_LINK ${libnetwork} ${libpropagation} ${libenergy}
                    ${libspectrum} ${libcore} ${libmobility}
                    ${libclock}
)
