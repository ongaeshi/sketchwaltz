# coding: utf-8
Graphics.set_background

font = Font.new(50)

while System.update do
  #Circle.new(Point.new(100, 100), 100).draw
  #Circle.new(Point.new(200, 200), 50).draw
  #Circle.new(Point.new(250, 250), 25).draw
  #Circle.new(Point.new(275, 275), 12.5).draw
  #Circle.new(Point.new(275+12.5, 275+12.5), 12.5/2).draw
  #Circle.new(Point.new(275+12.5+12.5/2, 275+12.5+12.5/2), 12.5/4).draw
  #Circle.new(Point.new(275+12.5+12.5/2+12.5/4, 275+12.5+12.5/2+12.5/4), 12.5/8).draw

  Circle.new(Cursor.pos, 100).draw

  font["Hello, Siv3D!🐣🐳👹👺"].draw

  # str = "こんにちは"
  # str = "🐕"
  # str = "😹"
  # font["こんにちは"].draw
  # font[Mouse.pos.to_s].draw
  # font["マウス座標: #{Mouse.pos}"].draw
  # font[Mouse.pos].draw(50, 200)
  # font[Mouse.pos].draw(50, 200, Pallete::Orange)
end
