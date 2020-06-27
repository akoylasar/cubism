// Copyright (c) Fouad Valadbeigi (akoylasar@gmail.com)
// UAV OSD Font by Nicholas Kruse at https://nicholaskruse.com

#pragma once

#include <string>
#include <cstdint>

namespace Cubism
{
  const std::string kFontDataAsBase64 = 
  "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"
  "AAUAAAAAC20QAAAHAA8AFwAfACUAAAETEQMhAxETAwERASEBEQkBExEDIQMREwMBEQEhAREJAREBIREBCbaTk/7ckpKS/tsBJQJJAST+3PiSkpL+25KSkv7cASQCSQEl/tv+SQduASX4kgJJASQCSQ"
  "El/tv9t/7c/tsCSQJJAkr9tv23/bcIAAElAkkBJP7c/bf+2/7cAkkCSQJJ/bf9t/23+AABJA7c/tvxJQADAAAAAAttEAAABQANACYAAAkCIREJAhEBIQERCQIRCQERASEBEQkBFRc3IREJAREhATUn"
  "AQW2ASX9t/23ASQCSQEl/tv9t/7cAST+3P23AST+3AJJBJICSf23ASWSkgJJ/twBJP7c/tuS/kkCSQEkAkn9t/7cBtsBJQJJAST+3P23/tv23AJJBJIBJQEkBJICSv22+279t/7bAZGS/tz+2/7c/b"
  "cBJAGR/koAAQSSC20G2xAAAAcAAAERASERIREBBJIBJP7cAkn9twttASUBJAJK/bb9twABA20AAAgAEAAACwAAIQERASERIQERASERBbb9twJJAkr+2/7bASUBJQJJC20CSv7b/tv0k/7b/twAAAAB"
  "A20AAAgAEAAACwAAIREhAREBIREhAREBA20BJQEk/tz+2wJJAkr9tgEkASULbQElASX9tvST/bcAAAABAAABJAttDtsAFQAAAREBIREJAREhAREhEQEhEQkBESEBEQSS/JL+3ANt/JMBJANuAkkDbg"
  "Ek/JMDbf7c/JIBJASS/JMCSQNuA20CSfyTBJL7bgNt/bf8k/yS/bcDbftuAAAAAQEkAkkKSQ22AAsAAAERIREhESERIREhEQSS/JIDbgJJA278kgJJBJICSQSS+279t/tuAAEEkv23BtsCSQAHAAAB"
  "EQEhESERAQSSAST+3AJJ/bf9twElASQCSf23/bcAAQEkBtsKSQkkAAMAAAERIREBJAklBtsCSf23AAEEkgAABtsCSQADAAAhESERBJICSQJJ/bcAAAABAAAAAArbEAAAAwAAMQEhAQgAAtv4ABAA8A"
  "AAAwAAAAAKSRAAAAMACAAQAAAJAREJAiEBGQEBEQEhAREBBtsBJftt/twFJPwA/tz9twJJBbcCSf23AkkBJAgA9twBJApJ/tz22/yTAkkLbQJK/bb0k/23AAECSQAACSQQAAAKAAAhESERIREBIREh"
  "EQJJAkn9twJJAkkCSQJJCSQCSQJK8kn9twAAAAABAAAAAAttEAAAEAAAMREBEQEhAREhEQEhAREBIREJJP7c+23+3P23AkkG2wJJ+AAIAAJJCSQBJQEk/tz+2wJJAkr9tvyT+AD9twAAAQAAAAALbR"
  "AAABwAACEBESERASEBEQEhESEBEQEhAREhEQEhAREJAREBAkn9twJJASQEkwEk/tz8kgNuAST+3Ptt/tz9twJJBtsCSf7cAST9twJJAkn+2/7cASQCSQElAkkBJQJJAST+3P7bAkkCSv22+27+3P7b"
  "+279twAAAAABAAAAAAttEAAAEQAAIREhEQEhESEBESERIREhESERCAD4AAgAAkn+2/klBbcCSQEk/twCSQW3CAD9tvkl/bcDbvyS/bf9twABAAAAAAttEAAAEwAAIQERIREBIQERASERIREhESEBEQ"
  "ECSf23AkkBJASTAST+3PgACkn4AAbbAkn9twJJA239t/7cASQDbgElCAD9tvyT/bf6Sf23AAAAAgAAAAALbRAAAAcAFAAACQERASEBEQkCEQkBIREhASEBEQEIAAEk/tz7bf7cAST+3P23ASQFtwJJ"
  "/tz7bQW3Akn9twJJASQCSQEl/tv9t/7c/bcCSQW3AkkFt/22+279t/tu/bcAAAABAAAAAAttEAAACQAAMREBESERIREBEQkk9twLbfbcAkkJJAJJAkr6Sfbb/twAAAADAAAAAAttEAAABwAPAB0AAA"
  "kBEQEhAREJAhEBIQERCQIRCQERASEBEQkBEQEIAAEk/tz7bf7cASQEkwEk/tz7bf7cAST+3P23AST+3AJJBtsCSf7cAST9twJJASQCSQEl/tv9t/7cBtsBJQJJAST+3P23/tv23AJJBJIBJQEkBJIC"
  "Sv22+27+3P7b+279twACAAAAAAttEAAABwAUAAAJAREBIQERCQERIQEhAREBIQERCQEIAAEk/tz7bf7cAST+3AEkBJP6Sf23AkkG2wJJ/tz6SQkkASUCSQEk/tz9t/7b9twCSQSSAkkEkgJK/bb6Sv"
  "22+koAAAIEkgJJBtsLbQADAAcAAAERIREBESERBJICSf23AkkCSQJJ/bcG2wJJ/bcAAgSSAAAG2wttAAcACwAAIREBIREhEQEZASERBJIBJP7cAkn9twJJASQBJQJJ/bf9twkkAkn9twABASQBJApJ"
  "DtsABwAACQIhEQkBEQgA+SQG3AJJ+kkFtwEkBtwG2/7b+kr6Sf7bAAACASQEkgpJC20AAwAHAAABESERAREhEQEkCSX22wklBJICSf23BJICSf23AAEBJAEkCkkO2wAHAAABEQkBESEJAQEkBbf6SQ"
  "JJBtz5JAEkASUFtwW2ASX5JfkkAAIAAAAAC20QAAADABMAACERIREBEQERASEBESERASEBEQERBJICSf23BJL+3Ptt/tz9twJJBtsCSftuAkn9twSSAkkEkgElAST+3P7bAkkCSv22/JP7bf7cAAAA"
  "AgAAASQLbQ7bAAMAHwAAAREhEQkBEQEhAREBIQEhAREBIQERIREhEQEhAREBIREG2/23/bf9twJJBtsCSf7c/bf+2/23/bcCSQJJASUBJAEl/bf7bf23AkkG3AbbAkn9t/pJAkkJJQJJ/bf4AP7bAS"
  "UCSQJJAkn+3AEk+kkFtwJJ/bf5Jf23/tsAAAACAAAAAAttEAAABQAPAAABEQEhAREBEQEhAREhESERCST9t/23/bf9twNtBJMDbf23+SUIAANtAkn9t/yT+AAMkgNu/JLzbgW2+koAAwAAAAALbRAA"
  "AAUACwAUAAAJAREBIREJAREBIREBESEBEQkBEQEIAAEk/tz6SQW3AST+3PpJ/bcJJAJJ/twBJP23AkkBJAJJASX7bgbbASUCSQEk+2723BAA/bb7bv7c/tv7bv23AAABAAAAAAttEAAAEwAAIQERAS"
  "EBESERASEBEQEhAREhEQECSf23AkkG2wJJ/bf+3Ptt/twBJASTASQCSf23AkkLbQJK/bb9twElAST+3Pbb/twBJAEl/bf9twAAAAIAAAAAC20QAAAFAAsAAAkBEQEhEQERIQERAQbbAkn9t/tu/bcI"
  "AANt/JMCSQJJBtsCSfST/bcQAPyS9tv8kwABAAAAAAttEAAACwAAMREhESERIREhESERC2323ASS+24JJBAA/bb7bv23+279twABAAAAAAttEAAACQAAMREhESERIREhEQtt9twEkvtuEAD9tvtu/b"
  "f5JQAAAAEAAAAAC20QAAAVAAAhAREBIQERIREBIQERASEBESERIREBAkn9twJJBtsCSf23/tz7bf7cASQEkwEk/twDbf23AkkLbQJK/bb9twElAST+3Pbb/twBJAJJAkr6Sf23AAEAAAAAC20QAAAL"
  "AAAxESERIREhESERIRECSQbbAkn9t/klEAD5JAbc8AAG2/klAAEAAAAAC20QAAALAAAxESERIREhESERIREEkvtuC237bgSSAkkLbQJK/bb0k/23AAEAAAAAC20QAAAPAAAhAREhEQEhAREhESERIR"
  "EBAkn9twJJASQCSQEl+24JJP23/bcCSQJJ/tv+3AEkCkkCSv229JP9twAAAAEAAAAAC20QAAAMAAAxESERASERCQERIQERAkkG2wJJ+SUG2/23+SUQAPkkBtz+2/kl+ST+3Abb+SUAAAEAAAAAC20Q"
  "AAAFAAAxESERIRECSQkkEADySf23AAAAAQAAAAALbRAAAAsAADERIQkBIREhEQkBEQJJA20DbgJJ/bf8kvyTEAD8kgNu8AAMkvySA27zbgABASQAAAttEAAACQAAIREhAREhESEBEQEkAkkFtwJJ/b"
  "f6SRAA9JILbvAAC230kwACAAAAAAttEAAABwAPAAAJAREBIQERCQIRASEBEQEIAAEk/tz7bf7cAST+3P23AkkG2wJJ/bcCSQEkCSUBJP7c9tv+3P23AkkLbQJK/bb0k/23AAACAAAAAAttEAAABQAN"
  "AAAJAREBIREBESEBEQEhEQgAAST+3PpJ/bcJJAJJ/bf5JQkkASUCSQEk+2723BAA/bb7bv23+SUAAAACAAAAAAttEAAACgAYAAAJAREhAREBIQERCQIRASEBEQkBESE1JwcG2/7bASUCSf7c+23+3A"
  "Ek/tz9twJJBtsCSf7cAST9t5KSAkkBJAJJ/bcJJQEk/tz22/7c/bcCSQttAkr9tvW3/tz+2/7cAZGSAAAAAAIAAAAAC20QAAAFABIAAAkBEQEhEQERIQERASMBESEBIREIAAEk/tz6Sf23CSQCSf23"
  "kgLb/bf8kvyTCSQBJQJJAST7bvbcEAD9tvtu/bf6Sf7cBtv5JQABAAAAAAttEAAAGwAAIQERIREBIQERASEBEQEhAREhEQEhAREBIQERAQJJ/bcCSQEkBJMBJP7c+kn9twJJBtsCSf23/tz7bf7cAS"
  "QFtwJJ/bcCSQJJ/tv+3AEkAkkBJQJJBJICSv22/bcBJQEk/tz9t/7b/bf7bv23AAAAAQAAAAALbRAAAAcAACERIREhESERBJL7bgtt+24NtgJK/bbySgAAAAEAAAAAC20QAAALAAAhAREhEQEhAREh"
  "EQECSf23AkkBJASTASQCSf23AkkNt/Nt/twBJAyT8kn9twAAAAEAAAAAC20QAAAKAAAhAREhEQkBESERAQSS+24CSQNtA24CSftuCSQG3PpJ+SQG3AW3+ST23AAAAQAAAAALbRAAAAsAADERIREJAR"
  "EhESEJAQJJA20DbgJJ/bf8kvyTEADzbQNu/JIMk/AAA238kwABAAAAAAttEAAADwAAMREJAREhCQEhEQkBESEJAQNt/JMCSQNtA24CSfyTA239t/yS/JMBJAbcBtsBJfkkBtz+2/kl+ST+3Abb+SUA"
  "AQAAAAALbRAAAAoAACERAREhCQEhEQERBJL7bgJJA20DbgJJ+24FtgklASX5JAbc/tv22/pKAAABAAAAAAttEAAACgAAMREBIREhEQERIREJJPbcC2323AkkBJIJJAJK/JL22/7c/bcAAAAAAQNtAA"
  "AIABAAAAcAACERIREhESERA20Ek/22AkoQAP7b8kn+3AAAAAEAkgAAC20QAAADAAAhASEBCJL4AALbCAAQAPAAAAAAAQNtAAAIABAAAAcAACERIREhESERA20CSf23BJMBJA23ASXwAAAAAAEAAAgA"
  "C20QAAAHAAAZAQkBESEJAQW2Bbf+3Ptt+24IAAJJBbf6Sf23BJL7bgAAAAEAAAAAC20CSQADAAAxESERC20CSf23AAEDbQttCAAQAAAFAAAJAREhAREG2/ySAtwBtwttA24BJfyS/tsAAAACAAAAAA"
  "ttEAAABQAPAAABEQEhAREBEQEhAREhESERCST9t/23/bf9twNtBJMDbf23+SUIAANtAkn9t/yT+AAMkgNu/JLzbgW2+koAAwAAAAALbRAAAAUACwAUAAAJAREBIREJAREBIREBESEBEQkBEQEIAAEk"
  "/tz6SQW3AST+3PpJ/bcJJAJJ/twBJP23AkkBJAJJASX7bgbbASUCSQEk+2723BAA/bb7bv7c/tv7bv23AAABAAAAAAttEAAAEwAAIQERASEBESERASEBEQEhAREhEQECSf23AkkG2wJJ/bf+3Ptt/t"
  "wBJASTASQCSf23AkkLbQJK/bb9twElAST+3Pbb/twBJAEl/bf9twAAAAIAAAAAC20QAAAFAAsAAAkBEQEhEQERIQERAQbbAkn9t/tu/bcIAANt/JMCSQJJBtsCSfST/bcQAPyS9tv8kwABAAAAAAtt"
  "EAAACwAAMREhESERIREhESERC2323ASS+24JJBAA/bb7bv23+279twABAAAAAAttEAAACQAAMREhESERIREhEQtt9twEkvtuEAD9tvtu/bf5JQAAAAEAAAAAC20QAAAVAAAhAREBIQERIREBIQERAS"
  "EBESERIREBAkn9twJJBtsCSf23/tz7bf7cASQEkwEk/twDbf23AkkLbQJK/bb9twElAST+3Pbb/twBJAJJAkr6Sf23AAEAAAAAC20QAAALAAAxESERIREhESERIRECSQbbAkn9t/klEAD5JAbc8AAG"
  "2/klAAEAAAAAC20QAAALAAAxESERIREhESERIREEkvtuC237bgSSAkkLbQJK/bb0k/23AAEAAAAAC20QAAAPAAAhAREhEQEhAREhESERIREBAkn9twJJASQCSQEl+24JJP23/bcCSQJJ/tv+3AEkCk"
  "kCSv229JP9twAAAAEAAAAAC20QAAAMAAAxESERASERCQERIQERAkkG2wJJ+SUG2/23+SUQAPkkBtz+2/kl+ST+3Abb+SUAAAEAAAAAC20QAAAFAAAxESERIRECSQkkEADySf23AAAAAQAAAAALbRAA"
  "AAsAADERIQkBIREhEQkBEQJJA20DbgJJ/bf8kvyTEAD8kgNu8AAMkvySA27zbgABASQAAAttEAAACQAAIREhAREhESEBEQEkAkkFtwJJ/bf6SRAA9JILbvAAC230kwACAAAAAAttEAAABwAPAAAJAR"
  "EBIQERCQIRASEBEQEIAAEk/tz7bf7cAST+3P23AkkG2wJJ/bcCSQEkCSUBJP7c9tv+3P23AkkLbQJK/bb0k/23AAACAAAAAAttEAAABQANAAAJAREBIREBESEBEQEhEQgAAST+3PpJ/bcJJAJJ/bf5"
  "JQkkASUCSQEk+2723BAA/bb7bv23+SUAAAACAAAAAAttEAAACgAYAAAJAREhAREBIQERCQIRASEBEQkBESE1JwcG2/7bASUCSf7c+23+3AEk/tz9twJJBtsCSf7cAST9t5KSAkkBJAJJ/bcJJQEk/t"
  "z22/7c/bcCSQttAkr9tvW3/tz+2/7cAZGSAAAAAAIAAAAAC20QAAAFABIAAAkBEQEhEQERIQERASMBESEBIREIAAEk/tz6Sf23CSQCSf23kgLb/bf8kvyTCSQBJQJJAST7bvbcEAD9tvtu/bf6Sf7c"
  "Btv5JQABAAAAAAttEAAAGwAAIQERIREBIQERASEBEQEhAREhEQEhAREBIQERAQJJ/bcCSQEkBJMBJP7c+kn9twJJBtsCSf23/tz7bf7cASQFtwJJ/bcCSQJJ/tv+3AEkAkkBJQJJBJICSv22/bcBJQ"
  "Ek/tz9t/7b/bf7bv23AAAAAQAAAAALbRAAAAcAACERIREhESERBJL7bgtt+24NtgJK/bbySgAAAAEAAAAAC20QAAALAAAhAREhEQEhAREhEQECSf23AkkBJASTASQCSf23AkkNt/Nt/twBJAyT8kn9"
  "twAAAAEAAAAAC20QAAAKAAAhAREhEQkBESERAQSS+24CSQNtA24CSftuCSQG3PpJ+SQG3AW3+ST23AAAAQAAAAALbRAAAAsAADERIREJAREhESEJAQJJA20DbgJJ/bf8kvyTEADzbQNu/JIMk/AAA2"
  "38kwABAAAAAAttEAAADwAAMREJAREhCQEhEQkBESEJAQNt/JMCSQNtA24CSfyTA239t/yS/JMBJAbcBtsBJfkkBtz+2/kl+ST+3Abb+SUAAQAAAAALbRAAAAoAACERAREhCQEhEQERBJL7bgJJA20D"
  "bgJJ+24FtgklASX5JAbc/tv22/pKAAABAAAAAAttEAAACgAAMREBIREhEQERIREJJPbcC2323AkkBJIJJAJK/JL22/7c/bcAAAAAAQJJAAAJJBAAABMAACEBEQERAREBIREhAREBEQERASERBbb+3P"
  "23AkkBJANu/tz+2/23AkkBJQEkAkkBJAJJBJMCSQEkAkr+2/23/tv9t/23/bf+2/23/twAAAABBJIAAAbbEAAAAwAAIREhEQSSAkkQAPAAAAAAAQJJAAAJJBAAABMAACERIQERAREBEQEhESEBEQER"
  "AREBAkkBJAElAkn9t/7b/twDbQElAkn9t/7bASQCSQElAkkCSQJJASUCSQEl/bb+3P23+239t/7c/bcAAAABAAAFtgttCkkADQAAGQEBIQEhASERASEBIQEDbQElAkkBJQJJAST8k/7b/bf+2/23Bb"
  "YBJQNu/bcCSf7b/JICSv22AAICSQkkCSQQAAADABcAAAERIRkCIREhESERIREhESERIREhESERBtv9t/7b/twBJAElAkkBJQEk/tz+2wttAkn9t/23ASUBJAJJASUBJf7b/tv9t/7c/tsAAAAAAQSS"
  "C20G2xAAAAYAAAERAREBIREEkgJJ/tsBJQttAkkCSv7b/tv9twAAAAABBJILbQbbEAAABwAAAREBIREhEQEEkgEk/twCSf23C20BJQEkAkr9tv23AAIDbQttCSQQAAAGAA0AAAERAREBIREhEQERAS"
  "ERA20CSf7cASQBJQJJ/twBJAttAkkCSv7b/tv9twJJAkr+2/7b/bcAAgNtC20JJBAAAAcADwAAAREBIREhEQEhEQEhESERAQNtASX+2wJJ/bcDbgEl/tsCSf23C20BJQEkAkr9tv23ASUBJAJK/bb9"
  "twAAAAAAFAD2AAEAAAAAAAAAAAACAAEAAAAAAAEAEQAnAAEAAAAAAAIABwBJAAEAAAAAAAMAEQB1AAEAAAAAAAQAEQCrAAEAAAAAAAUACwDVAAEAAAAAAAYAEQEFAAEAAAAAAAkADgE1AAEAAAAAAA"
  "wAGQF4AAEAAAAAABMAOAIEAAMAAQQJAAAAAAAAAAMAAQQJAAEAIgADAAMAAQQJAAIADgA5AAMAAQQJAAMAIgBRAAMAAQQJAAQAIgCHAAMAAQQJAAUAFgC9AAMAAQQJAAYAIgDhAAMAAQQJAAkAHAEX"
  "AAMAAQQJAAwAMgFEAAMAAQQJABMAcAGSAAAAAFUAQQBWACAATwBTAEQAIABTAGEAbgBzACAATQBvAG4AbwAAVUFWIE9TRCBTYW5zIE1vbm8AAFIAZQBnAHUAbABhAHIAAFJlZ3VsYXIAAFUAQQBWAC"
  "AATwBTAEQAIABTAGEAbgBzACAATQBvAG4AbwAAVUFWIE9TRCBTYW5zIE1vbm8AAFUAQQBWACAATwBTAEQAIABTAGEAbgBzACAATQBvAG4AbwAAVUFWIE9TRCBTYW5zIE1vbm8AAFYAZQByAHMAaQBv"
  "AG4AIAAxAC4AMAAAVmVyc2lvbiAxLjAAAFUAQQBWAC0ATwBTAEQALQBTAGEAbgBzAC0ATQBvAG4AbwAAVUFWLU9TRC1TYW5zLU1vbm8AAE4AaQBjAGgAbwBsAGEAcwAgAEsAcgB1AHMAZQAATmljaG"
  "9sYXMgS3J1c2UAAGgAdAB0AHAAcwA6AC8ALwBuAGkAYwBoAG8AbABhAHMAawByAHUAcwBlAC4AYwBvAG0AAGh0dHBzOi8vbmljaG9sYXNrcnVzZS5jb20AAFQAaABlACAAcQB1AGkAYwBrACAAYgBy"
  "AG8AdwBuACAAZgBvAHgAIABqAHUAbQBwAHMAIABvAHYAZQByACAAdABoAGUAIABsAGEAegB5ACAAZABvAGcALgAgACAAMQAyADMANAA1ADYANwA4ADkAMAAAVGhlIHF1aWNrIGJyb3duIGZveCBqdW"
  "1wcyBvdmVyIHRoZSBsYXp5IGRvZy4gIDEyMzQ1Njc4OTAAAAACAAAAAAAAAZkAzAAAAAAAAAAAAAAAAAAAAAAAAAAAAGcAAAECAQMAAwAEAAUABgAHAAgACQAKAAsADAANAA4ADwAQABEAEgATABQA"
  "FQAWABcAGAAZABoAGwAcAB0AHgAfACAAIQAiACMAJAAlACYAJwAoACkAKgArACwALQAuAC8AMAAxADIAMwA0ADUANgA3ADgAOQA6ADsAPAA9AD4APwBAAEEAQgBDAEQARQBGAEcASABJAEoASwBMAE"
  "0ATgBPAFAAUQBSAFMAVABVAFYAVwBYAFkAWgBbAFwAXQBeAF8AYABhAIMAtgC3ALQAtQZnbHlwaDEGZ2x5cGgyAAAAAAAB//8AAgABAAAADAAAABYAHgACAAEAAQBmAAEABAAAAAIAAAABAAAAAQAA"
  "AAAAAQAAAAoAHAAeAAFsYXRuAAgABAAAAAD//wAAAAAAAAABAAAACgAeACwAAWxhdG4ACAAEAAAAAP//AAEAAAABa2VybgAIAAAAAQAAAAEABAACAAAAAQAIAAEAJAAEAAAABAASABgAGAAeAAEAKA"
  "AAAAEALAAAAAEAKgAAAAEABAAkACoAKwAsAAAAAQAAAADakgP3AAAAANrNe2MAAAAA2tp+yg==";
  const std::uint8_t kGlyphRanges[2] = { 0x20, 0xFF };
}















