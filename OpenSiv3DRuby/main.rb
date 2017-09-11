Graphics.set_background([204, 230, 255])

font = Font.new(50)
cat = Texture.new(Emoji.new("🐈"), TextureDesc::Mipped)

point = Point.new(1, 2)
vec = Vec2.new(1.5, 2.1)
p Point, point.x, point.y
puts "#{Vec2}: (#{vec.x}, #{vec.y})"

while System.update do
  c = Cursor.pos
  Circle.new(600, 15, 15).draw(ColorF.new(1, 1, 1, 0.5))
  Rect.new(90, 228, 40, 150).draw(Palette::Yellowgreen)
  Circle.new(c.x, c.y, 50).draw([255, 0, 0, 128])
  Rect.new(150, 228, 40, 150).draw(Palette::Yellowgreen)
  cat.scale(2, 2).draw(0, 0)
  font["こんにちは"].draw(0, 0)
  font["Hello, Siv3D!🐣\n#{c}"].draw_at(Window.center.x, Window.center.y, Palette::Black)
  cat.resize(80, 80).draw(540, 380)
end
