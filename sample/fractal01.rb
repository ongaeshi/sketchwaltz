Graphics.set_background(Palette::White)

def draw_circle(x, y, radius, color = Palette::Black)
  Circle.new(x, y, radius).draw_frame(1, color)
  if radius > 8
    draw_circle(x + radius/2, y, radius/2, Palette::Black)
    draw_circle(x - radius/2, y, radius/2, Palette::Red)
    draw_circle(x, y + radius/2, radius/2, Palette::Green)
    draw_circle(x, y - radius/2, radius/2, Palette::Blue)
  end
end

camera = Camera2D.new

while System.update do
  camera.update
  camera.draw(Palette::Orange)
  camera.transform do
    draw_circle(Window.width/2, Window.height/2, 1000)
  end
end
