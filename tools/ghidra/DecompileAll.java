// Ghidra headless script: decompile every function into one C file (for searching).
// Usage: -postScript DecompileAll.java <out_file>
//@category SW2EPC
import ghidra.app.decompiler.DecompInterface;
import ghidra.app.decompiler.DecompileResults;
import ghidra.app.script.GhidraScript;
import ghidra.program.model.listing.Function;

import java.io.File;
import java.io.PrintWriter;

public class DecompileAll extends GhidraScript {
    @Override
    public void run() throws Exception {
        DecompInterface dec = new DecompInterface();
        dec.openProgram(currentProgram);
        int done = 0, failed = 0;
        try (PrintWriter w = new PrintWriter(new File(getScriptArgs()[0]))) {
            for (Function f : currentProgram.getFunctionManager().getFunctions(true)) {
                if (monitor.isCancelled()) break;
                DecompileResults res = dec.decompileFunction(f, 60, monitor);
                w.printf("// ==== %s at 0x%08x, %d bytes ====%n", f.getName(),
                         f.getEntryPoint().getOffset(), f.getBody().getNumAddresses());
                if (res.decompileCompleted()) {
                    w.println(res.getDecompiledFunction().getC());
                    done++;
                } else {
                    w.println("// failed: " + res.getErrorMessage());
                    failed++;
                }
            }
        }
        println("DecompileAll: " + done + " decompiled, " + failed + " failed");
    }
}
