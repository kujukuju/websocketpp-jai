#import "Bindings_Generator";
#import "Basic";
#import "File";
#import "String";
#import "BuildCpp";
#import "File_Utilities";

#run {
    using opts: Generate_Bindings_Options;
    array_add(*system_include_paths, GENERATOR_DEFAULT_SYSTEM_INCLUDE_PATH);

    array_add(*libpaths, "bin/win");
    array_add(*libnames, "websocketpp");
    // files := file_list(tprint("%websocketpp-jai/export/websocketpp/websocketpp", #filepath));
    // defer array_free(files);
    // for file: files {
    //     array_add(*include_paths, tprint("%websocketpp-jai/", #filepath));
    // }
    // array_add(*include_paths, tprint("%export/asio-1.28.0/include", #filepath));
    // array_add(*include_paths, tprint("%export/websocketpp/", #filepath));
    // array_add(*include_paths, tprint("%export/", #filepath));

    array_add(*source_files, tprint("%export/main.h", #filepath));

    // array_add(*extra_clang_arguments, "-D_WEBSOCKETPP_CPP11_STL_");
    // array_add(*extra_clang_arguments, "-D_GLIBCXX_USE_NANOSLEEP", "-DNO_VALIDATE", "-DASIO_STANDALONE", "-DENABLE_CPP11=TRUE", "-D_USE_MATH_DEFINES");
    array_add(*extra_clang_arguments, "-x", "c++");
    generate_compile_time_struct_checks = false;

    array_add(*system_include_paths, "C:\\Program Files (x86)\\Windows Kits\\10\\Include\\10.0.22621.0\\ucrt");
    array_add(*system_include_paths, "C:\\Program Files (x86)\\Windows Kits\\10\\Include\\10.0.22621.0\\um");
    array_add(*system_include_paths, "C:\\Program Files (x86)\\Windows Kits\\10\\Include\\10.0.22621.0\\shared");
    array_add(*system_include_paths, "C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\MSVC\\14.36.32532\\include");

    generate_bindings(opts, "module.jai");
}