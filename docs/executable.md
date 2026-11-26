# The executable: `SLES_546.24`

Analysed with `tools/disc_info.py`, `tools/elf_info.py` and `tools/find_strings.py`.

## Summary

| Property | Value |
|---|---|
| Format | 32-bit little-endian ELF, MIPS (R5900 / Emotion Engine) |
| Size | 3,529,520 bytes |
| MD5 | `0e0c852d8dc51a9517eb882d35bc7a30` |
| SHA-1 | `346e805e6b6b9b00c0df31d12659c59fcb55020d` |
| Code + data | a single unnamed segment loaded at `0x00100000` |
| Estimated code | `0x00100000`–`0x004050a8` (3,166,376 bytes), 11,128 `jr $ra` instructions |
| **Compiler** | **`MW MIPS C Compiler (2.4.1.01)`** (Metrowerks CodeWarrior for PS2), from the `.comment` section |
| Symbols | none (`.symtab` and `.strtab` are empty) |
| Debug info | none |
| Language | C (all named source files are `.c`) |

Several CodeWarrior PS2 releases (2.4 to 3.0.x) write the same `2.4.1.01` comment; the exact build
can only be found by compiling functions and comparing.

## Source files named in the executable

70 source file names survive in the binary (from `__FILE__` in assertion or error messages). They
give the original layout of the code and will name the translation units of the decompilation:

| Area | Files |
|---|---|
| Game states | `StateStartUp.c`, `StateInitialize.c`, `StateBattleInitialize.c`, `StatePreBattle.c`, `StatePostBattle.c`, `StateConquest.c`, `StateConfig.c`, `StateDemo.c`, `StateEdit.c`, `StateShop.c`, `StateTreasures.c`, `StateSetupEmpMogi.c` |
| Scenes | `SceneTitle.c`, `SceneLoading.c`, `ScenePreBattle.c`, `SceneTutorial.c`, `CSecretsScene.c` |
| Empire mode (`emp_*`) | `emp_cq_main.c`, `emp_cq_text.c`, `emp_war_fix.c`, `emp_war_tl.c`, `emp_war_wllt.c`, `emp_sc.c`, `emp_free_setup.c`, `emp_ending.c`, `emp_ending_nenpyou.c`, `emp_ev_predata.c`, `emp_ev_station.c`, `emp_ev_still.c`, `emp_FldBase.c`, `emp_zuroku.c`, `emp_zuroku_bushou.c`, `emp_zuroku_graph.c`, `emp_zuroku_movie.c`, `StationEmp.c` |
| Battle field and models | `Field.c`, `Stage.c`, `StgAmbient.c`, `StgTexture.c`, `DistantView.c`, `BgManager.c`, `ModelManager.c`, `MotionManager.c`, `HorseModel.c`, `FlagModel.c`, `ItemModel.c`, `Weapon.c`, `Bullet.c`, `ObjAction.c`, `RelayCamera.c`, `effect.c` |
| Maps and UI | `JapanMap.c`, `MiniMap.c`, `BriefingCmnParts.c`, `cmnparts.c`, `font.c`, `MovieTelop.c`, `SeasonAnime.c`, `SecretSorts.c` |
| Events and scripts | `ev_main.c`, `ev_config.c`, `ev_message.c`, `sc_ctrl.c`, `sc_sysmsg.c`, `sc_ubase.c` |
| System | `file.c`, `Gsaveload.c`, `SeManager.c`, `sd_call.c`, `P.c` |

(`zuroku` = encyclopedia/gallery, `bushou` = officers, `nenpyou` = chronology.)

## Paths used by the game

```
\LINKDATA.ANS   \LINKDATA.BNS   \LINKDATA.CNS
\MODULES\MODULES.BIN;1          cdrom0:\MODULES\IOPRP300.IMG;1
```
