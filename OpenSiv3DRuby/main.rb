# coding: utf-8
Graphics.set_background(ColorF.new(0.8, 0.9, 1.0))

font = Font.new(50)

while System.update do
  Circle.new(Cursor.pos, 60).draw
  font["Hello, Siv3D!🐣🐳👹👺"].draw
end

# Goal
# Graphics.set_background(ColorF.new(0.8, 0.9, 1.0))

# font = Font.new(50)
# cat = Texture.new(Emoji.new("🐈"), TextureDesc::Mipped)

# while System.update do
#   Circle.new(Cursor.pos, 60).draw(ColorF.new(1, 0, 0, 0.5))
#   font["Hello, Siv3D!🐣"].draw_at(Window.center, Palette::Black)
#   cat.resize(80).draw(540, 380)
#   cat.scale(Vec2.new(2.0, 2.0)).draw(0, 0)
# end
