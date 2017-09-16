Graphics.set_background([204, 230, 255])

font = Font.new(50)
cat = Texture.new(Emoji.new("🐈"), TextureDesc::Mipped)

point = Point.new(1, 2)
vec = Vec2.new(1.5, 2.1)
p Point, point.x, point.y
puts "#{Vec2}: (#{vec.x}, #{vec.y})"
puts "random: #{random}, #{random(10)}, #{random(3, 4)}"
puts "width: #{Window.width}, height: #{Window.height}"

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

  Rect.new(400, 300, 40, 100).draw_frame(4)
  Rect.new(450, 300, 40, 100).draw_frame(4, Palette::Navy)
  Rect.new(500, 300, 40, 100).draw_inner_outer(3, 0, Palette::Red)
  Rect.new(500, 300, 40, 100).draw_inner_outer(0, 6, Palette::Green)

  Line.new(100, 220, 300, 320).draw
  Line.new(100, 320, 300, 420).draw(2)
  Line.new(100, 420, 300, 520).draw(11, Palette::Green)
  Line.new(200, 100, 300, 100).draw_arrow
  Line.new(200, 150, 300, 150).draw_arrow(5)
  Line.new(200, 200, 300, 200).draw_arrow(5, Vec2.new(30, 20))
  Line.new(200, 250, 300, 250).draw_arrow(5, [50, 30], [255, 0, 128, 128])

  points = [
    [50, 350],
    [200, 400],
    [100, 450],
  ]

  Triangle.new(points[0], points[1], points[2]).draw
  Triangle.new(points[1], points[2], Vec2.new(100, 500)).draw(Palette::Hotpink)

  Quad.new([ 370, 405 ], [ 390, 405 ], [ 410, 440 ], [ 350, 440 ]).draw
  Quad.new([ 420, 405 ], [ 440, 405 ], [ 460, 440 ], [ 400, 440 ]).draw(Palette::Brown)

  RoundRect.new(305, 310, 40, 20, 8).draw
  RoundRect.new(355, 310, 40, 20, 16).draw(Palette::Teal)

  Polygon.new([
     [ 40, 10 ],
     [ 44, 24 ],
     [ 58, 24 ],
     [ 47, 32 ],
     [ 51, 46 ],
     [ 40, 38 ],
     [ 28, 46 ],
     [ 32, 32 ],
     [ 22, 24 ],
     [ 36, 24 ]
    ]).draw(Palette::Yellow)
end
