add_executable(srm2sav srm2sav.cxx)
add_executable(sav2srm sav2srm.cxx)

install(TARGETS srm2sav sav2srm DESTINATION "bin")

SetTargetCategory(srm2sav "")
SetTargetCategory(sav2srm "")
