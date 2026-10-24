.section ".text.crt0","ax"

.global __module_start
__module_start:
    // creport only reads a module's symbols when its first word is 0, the layout of modules loaded by rtld.
    // Subsdks are started by rtld through their init function (rtldInit), so the first word of our module is never executed.
    // See how atmosphere detects symbols used for crash reports:
    // https://github.com/Atmosphere-NX/Atmosphere/blob/c8c76bf8f8f6f9587de5d8ac1bd7090635353e9b/stratosphere/creport/source/creport_modules.cpp#L297-L335
    .word 0
    .word __nx_mod0 - __module_start // rtld reads the MOD0 header to find our dynamic section (imports, relocations, rtldInit...)


.section ".rodata.mod0","a"

.hidden __rtld_module_object__

.align 2
__nx_mod0:
    .ascii "MOD0"
    .word  __dynamic_start__        - __nx_mod0
    .word  __bss_start__            - __nx_mod0
    .word  __bss_end__              - __nx_mod0
    .word  __eh_frame_hdr_start__   - __nx_mod0
    .word  __eh_frame_hdr_end__     - __nx_mod0
    .word  __rtld_module_object__   - __nx_mod0
