# coding: utf-8
Graphics.set_background([204, 230, 255])

font = Font.new(50)
# cat = Texture.new("test.png")
cat = Texture.new(Emoji.new("🐈"), TextureDesc::Mipped)

while System.update do
  c = Cursor.pos
  Circle.new(c.x, c.y, 50).draw([255, 0, 0, 128])
  font["Hello, Siv3D!🐣\n#{c}"].draw_at(Window.center.x, Window.center.y, Palette::Black)
  cat.resize(80, 80).draw(540, 380)
  cat.scale(2, 2).draw(0, 0)
end

# Goal
# Graphics.set_background(ColorF.new(0.8, 0.9, 1.0))

# font = Font.new(50)
# cat = Texture.new(Emoji.new("🐈"), TextureDesc::Mipped)

# while System.update do
#   Circle.new(Cursor.pos, 60).draw(ColorF.new(1, 0, 0, 0.5))
#   font["Hello, Siv3D!🐣"].draw_at(Window.center, Palette::Black)
#   cat.resize(80).draw(540, 380)
#   cat.scale(2, 2).draw(0, 0)
# end
