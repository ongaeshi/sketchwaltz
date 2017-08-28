# $ mruby/bin/mrbc.exe -o __builtin.c -B mrb_siv3druby_builtin __builtin.rb

# mruby-print

##
# Kernel
#
# ISO 15.3.1
module Kernel
  ##
  # Invoke method +print+ on STDOUT and passing +*args+
  #
  # ISO 15.3.1.2.10
  def print(*args)
    i = 0
    len = args.size
    while i < len
      __printstr__ args[i].to_s
      i += 1
    end
  end

  ##
  # Invoke method +puts+ on STDOUT and passing +*args*+
  #
  # ISO 15.3.1.2.11
  def puts(*args)
    i = 0
    len = args.size
    while i < len
      s = args[i].to_s
      __printstr__ s
      __printstr__ "\n" if (s[-1] != "\n")
      i += 1
    end
    __printstr__ "\n" if len == 0
    nil
  end

  ##
  # Print human readable object description
  #
  # ISO 15.3.1.3.34
  def p(*args)
    i = 0
    len = args.size
    while i < len
      __printstr__ args[i].inspect
      __printstr__ "\n"
      i += 1
    end
    args[0]
  end

  unless Kernel.respond_to?(:sprintf)
    def printf(*args)
      raise NotImplementedError.new('printf not available')
    end
    def sprintf(*args)
      raise NotImplementedError.new('sprintf not available')
    end
  else
    def printf(*args)
      __printstr__(sprintf(*args))
      nil
    end
  end
end

# OpenSiv3DRuby

class Palette
  Black = [ 0,0,0 ]
  Dimgray = [ 105,105,105 ]
  Gray = [ 128,128,128 ]
  Darkgray = [ 169,169,169 ]
  Silver = [ 192,192,192 ]
  Lightgrey = [ 211,211,211 ]
  Gainsboro = [ 220,220,220 ]
  Whitesmoke = [ 245,245,245 ]
  White = [ 255,255,255 ]
  Snow = [ 255,250,250 ]
  Ghostwhite = [ 248,248,255 ]
  Floralwhite = [ 255,250,240 ]
  Linen = [ 250,240,230 ]
  Antiquewhite = [ 250,235,215 ]
  Papayawhip = [ 255,239,213 ]
  Blanchedalmond = [ 255,235,205 ]
  Bisque = [ 255,228,196 ]
  Moccasin = [ 255,228,181 ]
  Navajowhite = [ 255,222,173 ]
  Peachpuff = [ 255,218,185 ]
  Mistyrose = [ 255,228,225 ]
  Lavenderblush = [ 255,240,245 ]
  Seashell = [ 255,245,238 ]
  Oldlace = [ 253,245,230 ]
  Ivory = [ 255,255,240 ]
  Honeydew = [ 240,255,240 ]
  Mintcream = [ 245,255,250 ]
  Azure = [ 240,255,255 ]
  Aliceblue = [ 240,248,255 ]
  Lavender = [ 230,230,250 ]
  Lightsteelblue = [ 176,196,222 ]
  Lightslategray = [ 119,136,153 ]
  Slategray = [ 112,128,144 ]
  Steelblue = [ 70,130,180 ]
  Royalblue = [ 65,105,225 ]
  Midnightblue = [ 25,25,112 ]
  Navy = [ 0,0,128 ]
  Darkblue = [ 0,0,139 ]
  Mediumblue = [ 0,0,205 ]
  Blue = [ 0,0,255 ]
  Dodgerblue = [ 30,144,255 ]
  Cornflowerblue = [ 100,149,237 ]
  Deepskyblue = [ 0,191,255 ]
  Lightskyblue = [ 135,206,250 ]
  Skyblue = [ 135,206,235 ]
  Lightblue = [ 173,216,230 ]
  Powderblue = [ 176,224,230 ]
  Paleturquoise = [ 175,238,238 ]
  Lightcyan = [ 224,255,255 ]
  Cyan = [ 0,255,255 ]
  Aqua = [ 0,255,255 ]
  Turquoise = [ 64,224,208 ]
  Mediumturquoise = [ 72,209,204 ]
  Darkturquoise = [ 0,206,209 ]
  Lightseagreen = [ 32,178,170 ]
  Cadetblue = [ 95,158,160 ]
  Darkcyan = [ 0,139,139 ]
  Teal = [ 0,128,128 ]
  Darkslategray = [ 47,79,79 ]
  Darkgreen = [ 0,100,0 ]
  Green = [ 0,128,0 ]
  Forestgreen = [ 34,139,34 ]
  Seagreen = [ 46,139,87 ]
  Mediumseagreen = [ 60,179,113 ]
  Mediumaquamarine = [ 102,205,170 ]
  Darkseagreen = [ 143,188,143 ]
  Aquamarine = [ 127,255,212 ]
  Palegreen = [ 152,251,152 ]
  Lightgreen = [ 144,238,144 ]
  Springgreen = [ 0,255,127 ]
  Mediumspringgreen = [ 0,250,154 ]
  Lawngreen = [ 124,252,0 ]
  Chartreuse = [ 127,255,0 ]
  Greenyellow = [ 173,255,47 ]
  Lime = [ 0,255,0 ]
  Limegreen = [ 50,205,50 ]
  Yellowgreen = [ 154,205,50 ]
  Darkolivegreen = [ 85,107,47 ]
  Olivedrab = [ 107,142,35 ]
  Olive = [ 128,128,0 ]
  Darkkhaki = [ 189,183,107 ]
  Palegoldenrod = [ 238,232,170 ]
  Cornsilk = [ 255,248,220 ]
  Beige = [ 245,245,220 ]
  Lightyellow = [ 255,255,224 ]
  Lightgoldenrodyellow = [ 250,250,210 ]
  Lemonchiffon = [ 255,250,205 ]
  Wheat = [ 245,222,179 ]
  Burlywood = [ 222,184,135 ]
  Tan = [ 210,180,140 ]
  Khaki = [ 240,230,140 ]
  Yellow = [ 255,255,0 ]
  Gold = [ 255,215,0 ]
  Orange = [ 255,165,0 ]
  Sandybrown = [ 244,164,96 ]
  Darkorange = [ 255,140,0 ]
  Goldenrod = [ 218,165,32 ]
  Peru = [ 205,133,63 ]
  Darkgoldenrod = [ 184,134,11 ]
  Chocolate = [ 210,105,30 ]
  Sienna = [ 160,82,45 ]
  Saddlebrown = [ 139,69,19 ]
  Maroon = [ 128,0,0 ]
  Darkred = [ 139,0,0 ]
  Brown = [ 165,42,42 ]
  Firebrick = [ 178,34,34 ]
  Indianred = [ 205,92,92 ]
  Rosybrown = [ 188,143,143 ]
  Darksalmon = [ 233,150,122 ]
  Lightcoral = [ 240,128,128 ]
  Salmon = [ 250,128,114 ]
  Lightsalmon = [ 255,160,122 ]
  Coral = [ 255,127,80 ]
  Tomato = [ 255,99,71 ]
  Orangered = [ 255,69,0 ]
  Red = [ 255,0,0 ]
  Crimson = [ 220,20,60 ]
  Mediumvioletred = [ 199,21,133 ]
  Deeppink = [ 255,20,147 ]
  Hotpink = [ 255,105,180 ]
  Palevioletred = [ 219,112,147 ]
  Pink = [ 255,192,203 ]
  Lightpink = [ 255,182,193 ]
  Thistle = [ 216,191,216 ]
  Magenta = [ 255,0,255 ]
  Fuchsia = [ 255,0,255 ]
  Violet = [ 238,130,238 ]
  Plum = [ 221,160,221 ]
  Orchid = [ 218,112,214 ]
  Mediumorchid = [ 186,85,211 ]
  Darkorchid = [ 153,50,204 ]
  Darkviolet = [ 148,0,211 ]
  Darkmagenta = [ 139,0,139 ]
  Purple = [ 128,0,128 ]
  Indigo = [ 75,0,130 ]
  Darkslateblue = [ 72,61,139 ]
  Blueviolet = [ 138,43,226 ]
  Mediumpurple = [ 147,112,219 ]
  Slateblue = [ 106,90,205 ]
  Mediumslateblue = [ 123,104,238 ]
end
