// Ghidra headless script: decompile the functions containing the given addresses.
// Usage: -postScript DecompileAt.java <out_file> <hex address>...
//@category SW2EPC
import ghidra.app.decompiler.DecompInterface;
import ghidra.app.decompiler.DecompileResults;
import ghidra.app.script.GhidraScript;
import ghidra.program.model.listing.Function;

import java.io.File;
import java.io.PrintWriter;

public class DecompileAt extends GhidraScript {
    @Override
    public void run() throws Exception {
        String[] args = getScriptArgs();
        DecompInterface dec = new DecompInterface();
        dec.openProgram(currentProgram);
        try (PrintWriter w = new PrintWriter(new File(args[0]))) {
            for (int i = 1; i < args.length; i++) {
                Function f = getFunctionContaining(toAddr(Long.decode(args[i])));
                if (f == null) {
                    w.printf("// no function at %s%n%n", args[i]);
                    continue;
                }
                DecompileResults res = dec.decompileFunction(f, 120, monitor);
                w.printf("// ==== %s at 0x%08x, %d bytes (asked: %s) ====%n", f.getName(),
                         f.getEntryPoint().getOffset(), f.getBody().getNumAddresses(), args[i]);
                w.println(res.decompileCompleted() ? res.getDecompiledFunction().getC()
                                                   : "// failed: " + res.getErrorMessage());
            }
        }
    }
}
