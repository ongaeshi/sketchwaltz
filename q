[1mdiff --git a/OpenSiv3DRuby/Main.cpp b/OpenSiv3DRuby/Main.cpp[m
[1mindex ab06509..860cf02 100644[m
[1m--- a/OpenSiv3DRuby/Main.cpp[m
[1m+++ b/OpenSiv3DRuby/Main.cpp[m
[36m@@ -10,14 +10,24 @@[m
 #include "mruby.h"[m
 #include "mruby/compile.h"[m
 #include "mruby/string.h"[m
[32m+[m[32m#include "mruby/dump.h"[m[41m[m
[32m+[m[41m[m
[32m+[m[32mextern "C" const uint8_t __declspec(align(4)) mrb_siv3druby_builtin[];[m[41m[m
 [m
 namespace siv3druby {[m
[32m+[m[41m[m
     Siv3DRubyState fSiv3DRubyState;[m
 [m
[32m+[m[32m    void loadBuiltin(mrb_state* mrb)[m[41m[m
[32m+[m[32m    {[m[41m[m
[32m+[m[32m        mrb_load_irep(mrb, mrb_siv3druby_builtin);[m[41m[m
[32m+[m[32m    }[m[41m[m
[32m+[m[41m[m
     void mainLoop()[m
     {[m
         mrb_state* mrb = mrb_open();[m
 [m
[32m+[m[32m        loadBuiltin(mrb);[m[41m[m
         MrbCircle::Init(mrb);[m
         MrbColorF::Init(mrb);[m
         MrbDrawableText::Init(mrb);[m
[1mdiff --git a/OpenSiv3DRuby/OpenSiv3DRuby.vcxproj b/OpenSiv3DRuby/OpenSiv3DRuby.vcxproj[m
[1mindex 3a7a543..3014f7c 100644[m
[1m--- a/OpenSiv3DRuby/OpenSiv3DRuby.vcxproj[m
[1m+++ b/OpenSiv3DRuby/OpenSiv3DRuby.vcxproj[m
[36m@@ -220,6 +220,7 @@[m
     <ClCompile Include="mruby\src\version.c" />[m
     <ClCompile Include="mruby\src\vm.c" />[m
     <ClCompile Include="Util.cpp" />[m
[32m+[m[32m    <ClCompile Include="__builtin.c" />[m[41m[m
   </ItemGroup>[m
   <ItemGroup>[m
     <Image Include="engine\texture\box-shadow\128.png" />[m
[1mdiff --git a/OpenSiv3DRuby/OpenSiv3DRuby.vcxproj.filters b/OpenSiv3DRuby/OpenSiv3DRuby.vcxproj.filters[m
[1mindex c0b5a54..ab6afe0 100644[m
[1m--- a/OpenSiv3DRuby/OpenSiv3DRuby.vcxproj.filters[m
[1m+++ b/OpenSiv3DRuby/OpenSiv3DRuby.vcxproj.filters[m
[36m@@ -168,6 +168,9 @@[m
     <ClCompile Include="Util.cpp">[m
       <Filter>Source Files</Filter>[m
     </ClCompile>[m
[32m+[m[32m    <ClCompile Include="__builtin.c">[m[41m[m
[32m+[m[32m      <Filter>Source Files</Filter>[m[41m[m
[32m+[m[32m    </ClCompile>[m[41m[m
   </ItemGroup>[m
   <ItemGroup>[m
     <Image Include="Icon.ico">[m
[1mdiff --git a/OpenSiv3DRuby/main.rb b/OpenSiv3DRuby/main.rb[m
[1mindex a4ca895..7cf5bf0 100644[m
[1m--- a/OpenSiv3DRuby/main.rb[m
[1m+++ b/OpenSiv3DRuby/main.rb[m
[36m@@ -1,147 +1,4 @@[m
 # coding: utf-8[m
[31m-class Palette[m
[31m-  Black = [ 0,0,0 ][m
[31m-  Dimgray = [ 105,105,105 ][m
[31m-  Gray = [ 128,128,128 ][m
[31m-  Darkgray = [ 169,169,169 ][m
[31m-  Silver = [ 192,192,192 ][m
[31m-  Lightgrey = [ 211,211,211 ][m
[31m-  Gainsboro = [ 220,220,220 ][m
[31m-  Whitesmoke = [ 245,245,245 ][m
[31m-  White = [ 255,255,255 ][m
[31m-  Snow = [ 255,250,250 ][m
[31m-  Ghostwhite = [ 248,248,255 ][m
[31m-  Floralwhite = [ 255,250,240 ][m
[31m-  Linen = [ 250,240,230 ][m
[31m-  Antiquewhite = [ 250,235,215 ][m
[31m-  Papayawhip = [ 255,239,213 ][m
[31m-  Blanchedalmond = [ 255,235,205 ][m
[31m-  Bisque = [ 255,228,196 ][m
[31m-  Moccasin = [ 255,228,181 ][m
[31m-  Navajowhite = [ 255,222,173 ][m
[31m-  Peachpuff = [ 255,218,185 ][m
[31m-  Mistyrose = [ 255,228,225 ][m
[31m-  Lavenderblush = [ 255,240,245 ][m
[31m-  Seashell = [ 255,245,238 ][m
[31m-  Oldlace = [ 253,245,230 ][m
[31m-  Ivory = [ 255,255,240 ][m
[31m-  Honeydew = [ 240,255,240 ][m
[31m-  Mintcream = [ 245,255,250 ][m
[31m-  Azure = [ 240,255,255 ][m
[31m-  Aliceblue = [ 240,248,255 ][m
[31m-  Lavender = [ 230,230,250 ][m
[31m-  Lightsteelblue = [ 176,196,222 ][m
[31m-  Lightslategray = [ 119,136,153 ][m
[31m-  Slategray = [ 112,128,144 ][m
[31m-  Steelblue = [ 70,130,180 ][m
[31m-  Royalblue = [ 65,105,225 ][m
[31m-  Midnightblue = [ 25,25,112 ][m
[31m-  Navy = [ 0,0,128 ][m
[31m-  Darkblue = [ 0,0,139 ][m
[31m-  Mediumblue = [ 0,0,205 ][m
[31m-  Blue = [ 0,0,255 ][m
[31m-  Dodgerblue = [ 30,144,255 ][m
[31m-  Cornflowerblue = [ 100,149,237 ][m
[31m-  Deepskyblue = [ 0,191,255 ][m
[31m-  Lightskyblue = [ 135,206,250 ][m
[31m-  Skyblue = [ 135,206,235 ][m
[31m-  Lightblue = [ 173,216,230 ][m
[31m-  Powderblue = [ 176,224,230 ][m
[31m-  Paleturquoise = [ 175,238,238 ][m
[31m-  Lightcyan = [ 224,255,255 ][m
[31m-  Cyan = [ 0,255,255 ][m
[31m-  Aqua = [ 0,255,255 ][m
[31m-  Turquoise = [ 64,224,208 ][m
[31m-  Mediumturquoise = [ 72,209,204 ][m
[31m-  Darkturquoise = [ 0,206,209 ][m
[31m-  Lightseagreen = [ 32,178,170 ][m
[31m-  Cadetblue = [ 95,158,160 ][m
[31m-  Darkcyan = [ 0,139,139 ][m
[31m-  Teal = [ 0,128,128 ][m
[31m-  Darkslategray = [ 47,79,79 ][m
[31m-  Darkgreen = [ 0,100,0 ][m
[31m-  Green = [ 0,128,0 ][m
[31m-  Forestgreen = [ 34,139,34 ][m
[31m-  Seagreen = [ 46,139,87 ][m
[31m-  Mediumseagreen = [ 60,179,113 ][m
[31m-  Mediumaquamarine = [ 102,205,170 ][m
[31m-  Darkseagreen = [ 143,188,143 ][m
[31m-  Aquamarine = [ 127,255,212 ][m
[31m-  Palegreen = [ 152,251,152 ][m
[31m-  Lightgreen = [ 144,238,144 ][m
[31m-  Springgreen = [ 0,255,127 ][m
[31m-  Mediumspringgreen = [ 0,250,154 ][m
[31m-  Lawngreen = [ 124,252,0 ][m
[31m-  Chartreuse = [ 127,255,0 ][m
[31m-  Greenyellow = [ 173,255,47 ][m
[31m-  Lime = [ 0,255,0 ][m
[31m-  Limegreen = [ 50,205,50 ][m
[31m-  Yellowgreen = [ 154,205,50 ][m
[31m-  Darkolivegreen = [ 85,107,47 ][m
[31m-  Olivedrab = [ 107,142,35 ][m
[31m-  Olive = [ 128,128,0 ][m
[31m-  Darkkhaki = [ 189,183,107 ][m
[31m-  Palegoldenrod = [ 238,232,170 ][m
[31m-  Cornsilk = [ 255,248,220 ][m
[31m-  Beige = [ 245,245,220 ][m
[31m-  Lightyellow = [ 255,255,224 ][m
[31m-  Lightgoldenrodyellow = [ 250,250,210 ][m
[31m-  Lemonchiffon = [ 255,250,205 ][m
[31m-  Wheat = [ 245,222,179 ][m
[31m-  Burlywood = [ 222,184,135 ][m
[31m-  Tan = [ 210,180,140 ][m
[31m-  Khaki = [ 240,230,140 ][m
[31m-  Yellow = [ 255,255,0 ][m
[31m-  Gold = [ 255,215,0 ][m
[31m-  Orange = [ 255,165,0 ][m
[31m-  Sandybrown = [ 244,164,96 ][m
[31m-  Darkorange = [ 255,140,0 ][m
[31m-  Goldenrod = [ 218,165,32 ][m
[31m-  Peru = [ 205,133,63 ][m
[31m-  Darkgoldenrod = [ 184,134,11 ][m
[31m-  Chocolate = [ 210,105,30 ][m
[31m-  Sienna = [ 160,82,45 ][m
[31m-  Saddlebrown = [ 139,69,19 ][m
[31m-  Maroon = [ 128,0,0 ][m
[31m-  Darkred = [ 139,0,0 ][m
[31m-  Brown = [ 165,42,42 ][m
[31m-  Firebrick = [ 178,34,34 ][m
[31m-  Indianred = [ 205,92,92 ][m
[31m-  Rosybrown = [ 188,143,143 ][m
[31m-  Darksalmon = [ 233,150,122 ][m
[31m-  Lightcoral = [ 240,128,128 ][m
[31m-  Salmon = [ 250,128,114 ][m
[31m-  Lightsalmon = [ 255,160,122 ][m
[31m-  Coral = [ 255,127,80 ][m
[31m-  Tomato = [ 255,99,71 ][m
[31m-  Orangered = [ 255,69,0 ][m
[31m-  Red = [ 255,0,0 ][m
[31m-  Crimson = [ 220,20,60 ][m
[31m-  Mediumvioletred = [ 199,21,133 ][m
[31m-  Deeppink = [ 255,20,147 ][m
[31m-  Hotpink = [ 255,105,180 ][m
[31m-  Palevioletred = [ 219,112,147 ][m
[31m-  Pink = [ 255,192,203 ][m
[31m-  Lightpink = [ 255,182,193 ][m
[31m-  Thistle = [ 216,191,216 ][m
[31m-  Magenta = [ 255,0,255 ][m
[31m-  Fuchsia = [ 255,0,255 ][m
[31m-  Violet = [ 238,130,238 ][m
[31m-  Plum = [ 221,160,221 ][m
[31m-  Orchid = [ 218,112,214 ][m
[31m-  Mediumorchid = [ 186,85,211 ][m
[31m-  Darkorchid = [ 153,50,204 ][m
[31m-  Darkviolet = [ 148,0,211 ][m
[31m-  Darkmagenta = [ 139,0,139 ][m
[31m-  Purple = [ 128,0,128 ][m
[31m-  Indigo = [ 75,0,130 ][m
[31m-  Darkslateblue = [ 72,61,139 ][m
[31m-  Blueviolet = [ 138,43,226 ][m
[31m-  Mediumpurple = [ 147,112,219 ][m
[31m-  Slateblue = [ 106,90,205 ][m
[31m-  Mediumslateblue = [ 123,104,238 ][m
[31m-end[m
[31m-[m
 Graphics.set_background([204, 230, 255])[m
 [m
 font = Font.new(50)[m
