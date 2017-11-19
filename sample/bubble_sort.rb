Graphics.set_background(Palette::White)
font = Font.new(30)

camera = Camera2D.new

while System.update do
  camera.update

  camera.transform do
		Rect.new(0, 0, 640, 640).draw_inner_outer(2, 0, Palette::Gray)
    0.upto(100) do |x|
      font[random(100).to_i.to_s].draw(x*64, y*64, Palette::Black)
      Line.new(x*64, 0, x*64, y*64).draw(1, Palette::Gray)
    end

    a = ArrayDrawer.new([1, 2, 3])
    a.draw(0, 0)
  end

  camera.draw(Palette::Orange)
end
