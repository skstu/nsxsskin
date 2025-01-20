file(GLOB entries *)
foreach(entry ${entries})
  if(NOT (IS_DIRECTORY ${entry}) OR (NOT (EXISTS ${entry}/CMakeLists.txt)))
    continue()
  endif()
  # ====================================================================================
  get_filename_component(entry_name "${entry}" NAME)
  # ====================================================================================
  if(${entry_name} STREQUAL "componects"
     OR ${entry_name} STREQUAL "plugins"
     OR ${entry_name} STREQUAL "libs")
    add_subdirectory(${entry})
    #[[
 GFN_SET_TARGET_OUTDIR(${SOLUTION_ROOT_DIR} "bin" "objs" "libs")
 add_subdirectory(${entry})
 set(project_folder_name "")
 GFN_GET_TARGET_PROJECT_FOLDER_NAME(${entry} project_folder_name)
 set_target_properties(${entry_name} PROPERTIES FOLDER ${project_folder_name})
 GFN_SET_TARGET_OUTDIR("")
 ]]
  elseif(${entry_name} STREQUAL "installer" OR ${entry_name} STREQUAL
                                               "nsxsskin")
    gfn_set_target_outdir(${SOLUTION_ROOT_DIR} "bin" "objs" "libs")
    add_subdirectory(${entry})
    get_filename_component(base_path ${entry} DIRECTORY)
    file(RELATIVE_PATH project_folder_name ${PROJECT_SOURCE_DIR} ${base_path})
    set_target_properties(${entry_name} PROPERTIES FOLDER
                                                   ${project_folder_name})
    gfn_set_target_outdir("")
    # ====================================================================================
  elseif(${entry_name} STREQUAL "___backup__")

  else()

  endif()

endforeach(entry)
