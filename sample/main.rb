Graphics.set_background(Palette::Black)

font = Font.new(30)

while System.update do
  Circle.new(Cursor.pos.x, Cursor.pos.y, 30).draw(Palette::Indigo)
  Circle.new(Cursor.pos.x, Cursor.pos.y, 20).draw(Palette::Purple)
  font["🐣Hello, SketchWaltz!💃"].draw_at(Window.center.x, Window.center.y, Palette::White)
end
