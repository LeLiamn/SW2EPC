// Ghidra headless script: export functions, source-file string references and decompiled C.
// Usage (from tools/ghidra_analyze.py): -postScript ExportInfo.java <out_dir> [string_filter...]
//@category SW2EPC
import ghidra.app.decompiler.DecompInterface;
import ghidra.app.decompiler.DecompileResults;
import ghidra.app.script.GhidraScript;
import ghidra.program.model.address.Address;
import ghidra.program.model.listing.Data;
import ghidra.program.model.listing.DataIterator;
import ghidra.program.model.listing.Function;
import ghidra.program.model.listing.FunctionIterator;
import ghidra.program.model.symbol.Reference;

import java.io.File;
import java.io.PrintWriter;
import java.util.LinkedHashSet;
import java.util.Set;

public class ExportInfo extends GhidraScript {
    @Override
    public void run() throws Exception {
        String[] args = getScriptArgs();
        File out = new File(args.length > 0 ? args[0] : "ghidra_out");
        out.mkdirs();

        try (PrintWriter w = new PrintWriter(new File(out, "functions.csv"))) {
            w.println("address,size,name");
            FunctionIterator it = currentProgram.getFunctionManager().getFunctions(true);
            for (Function f : it) {
                w.printf("0x%08x,%d,%s%n", f.getEntryPoint().getOffset(),
                         f.getBody().getNumAddresses(), f.getName());
            }
        }

        Set<Function> wanted = new LinkedHashSet<>();
        try (PrintWriter w = new PrintWriter(new File(out, "string_refs.csv"))) {
            w.println("string_address,string,ref_from,function");
            DataIterator data = currentProgram.getListing().getDefinedData(true);
            for (Data d : data) {
                if (!d.hasStringValue()) continue;
                String s = String.valueOf(d.getValue());
                if (!s.endsWith(".c")) continue;
                for (Reference r : getReferencesTo(d.getAddress())) {
                    Function f = getFunctionContaining(r.getFromAddress());
                    w.printf("0x%08x,%s,0x%08x,%s%n", d.getAddress().getOffset(), s,
                             r.getFromAddress().getOffset(), f == null ? "" : f.getName());
                    for (int i = 1; i < args.length; i++) {
                        if (f != null && s.contains(args[i])) wanted.add(f);
                    }
                }
            }
        }

        DecompInterface dec = new DecompInterface();
        dec.openProgram(currentProgram);
        try (PrintWriter w = new PrintWriter(new File(out, "decompiled.c"))) {
            for (Function f : wanted) {
                DecompileResults res = dec.decompileFunction(f, 120, monitor);
                w.printf("// ==== %s at 0x%08x ====%n", f.getName(), f.getEntryPoint().getOffset());
                w.println(res.decompileCompleted() ? res.getDecompiledFunction().getC()
                                                   : "// decompilation failed: " + res.getErrorMessage());
            }
        }
        println("ExportInfo: done, " + wanted.size() + " functions decompiled");
    }
}
