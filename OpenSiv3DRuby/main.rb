Graphics.set_background([204, 230, 255])

font = Font.new(50)
cat = Texture.new(Emoji.new("🐈"), TextureDesc::Mipped)

point = Point.new(1, 2)
vec = Vec2.new(1.5, 2.1)
p Point, point.x, point.y
puts "#{Vec2}: (#{vec.x}, #{vec.y})"
puts "random: #{random}, #{random(10)}, #{random(3, 4)}"
puts "width: #{Window.width}, height: #{Window.height}"
puts "PI: #{Math::PI}, E: #{Math::E}"

rect = Rect.new(550, 50, 100, 40)
radian = 0

texture = Texture.new("Example/Windmill.png")

while System.update do
  texture.flip.draw
  texture.mirror.draw
  texture.draw
  texture.draw(100, 50)
  texture[260, 100, 200, 220].draw(20, 20)
  texture[260, 100, 200, 220].mirror.draw(350, 200)
  texture[260, 100, 200, 220].flip.draw(350, 200)
  texture.scale(0.5).draw
  texture.scale(1.0, 0.5).draw(0, 200)
  10.downto(1) do |e|
    texture[260, 100, 200, 220].scale(e * 0.1).draw(350, 200)
  end
  texture.resize(80, 80).draw
  texture[260, 100, 200, 220].resize(50, 50).draw
	texture.map(100, 200).draw
	texture.repeat(640, 480).draw(0, 0, [255, 255, 255, 64])
  texture.rotate(Math.radians(-15)).draw()
  texture[260, 100, 200, 220].rotate(Math.radians(15)).draw(350, 200)
  texture.rotate_at(0, 0, Math.radians(-15)).draw()
	texture[260, 100, 200, 220].rotate_at(50, 50, Math.radians(15)).draw(350, 200)
  Rect.new(100, 100, 300, 200)[texture].draw
  Rect.new(100, 100, 300, 200)[texture[260, 100, 200, 220]].draw
  Rect.new(100, 100, 300, 200).rotated(Math.radians(45))[texture].draw
  Rect.new(0, 0, 300, 300).draw
  texture.draw(100, 100, [255, 255, 255, 180])
  texture.draw(100, 100, [0, 255, 255])

  # Circle.new(350 + 50, 200 + 50, 3).draw
  Circle.new(530, 170, 30).draw_frame(5, Palette::Blue)

  circle = Circle.new(530, 250, 20)
  circle.draw_inner_outer(5, 0)
  circle.draw_inner_outer(0, 20, Palette::Brown)

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

  radian += Math.radians(1.2)
  rect.draw
  rect.rotated(radian).draw(Palette::Orange)

	LineString.new([
    [ 305, 10 ],
    [ 360, 10 ],
    [ 305, 20 ],
    [ 360, 20 ],
    [ 305, 30 ],
    [ 360, 30 ],
    [ 305, 40 ]
  ]).draw(3, Palette::Lightgoldenrodyellow)

	line_string = LineString.new([
    [ 405, 5 ],
    [ 420, 30 ],
    [ 440, 30 ],
    [ 410, 60 ],
    [ 450, 60 ]
  ])

  line_string.draw_catmull_rom(4, Palette::Darkslategray)
  line_string.draw_catmull_rom(1, Palette::Red, true, 36)

  #---
  c = Cursor.pos

  Circle.new(600, 15, 15).draw(ColorF.new(1, 1, 1, 0.5))
  Rect.new(90, 228, 40, 150).draw(Palette::Yellowgreen)
  Circle.new(c.x, c.y, 50).draw([255, 0, 0, 128])
  Rect.new(150, 228, 40, 150).draw(Palette::Yellowgreen)

  cat.scale(2, 2).draw(0, 0)
  font["こんにちは"].draw(0, 0)
  font["Hello, SketchWaltz!💃\n#{c}"].draw_at(Window.center.x, Window.center.y, Palette::Black)
  cat.resize(80, 80).draw(540, 380)
end
