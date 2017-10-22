$font = Font.new(50)
texture = Texture.new("Example/Windmill.png")
not_existing_texture = Texture.new("NOT_EXIST_TEXTURE.png")

def sample_case(title)
  is_pause = false
  rest = 60

  while rest > 0 do
    yield
    $font[title].draw(0, 380)

    if is_pause
      Rect.new(580, 15, 12, 35).draw([255, 255, 255, 128])
      Rect.new(600, 15, 12, 35).draw([255, 255, 255, 128])
      Rect.new(565, 0, 15 + 20 + 12 + 15, 65).draw([255, 255, 255, 128])
      is_pause ^= true if MouseL.down && Cursor.pos.x > 560 && Cursor.pos.y < 70
    else
      rest -= 1
      is_pause ^= true if MouseL.down
    end

    Fiber.yield
  end
end

fiber = Fiber.new do
  loop do
    sample_case("Circle") do
      Circle.new(300, 200, 150).draw
    end

    sample_case("Rect") do
      Rect.new(50, 100, 400, 200).draw
    end

    sample_case("Line") do
		  Line.new(50, 400, 600, 50).draw
      Line.new(50, 200, 600, 250).draw(5)
    end

    sample_case("Triangle") do
      Triangle.new([50, 50], [600, 400], [100, 400]).draw
    end

    sample_case("Quad") do
      Quad.new([ 200, 50 ], [ 400, 50 ], [ 600, 400 ], [ 0, 400 ]).draw
    end

    sample_case("Round Rect") do
      RoundRect.new(50, 100, 400, 200, 40).draw
    end

    sample_case("Polygon") do
	    star = Polygon.new([
		    [ 0, -200 ],[ 40, -60 ],
		    [ 180, -60 ],[ 75, 25 ],
		    [ 115, 160 ],[ 0, 80 ],
		    [ -115, 160 ],[ -75, 25 ],
		    [ -180, -60 ],[ -40, -60 ]
      ])

      star.draw
      star.moved_by(400, 300).draw
    end

    sample_case("Color") do
		  Circle.new(100, 100, 100).draw(Palette::Red)
		  Rect.new(150, 100, 200, 200).draw(Palette::Orange)
		  Line.new(50, 400, 600, 50).draw(3, [128, 255, 255]);
		  Circle.new(400, 400, 200).draw([0, 0, 255, 127]);
    end

    rect = Rect.new(100, 100, 400, 300)
    sample_case("Draw Frame") do
		  rect.draw_inner_outer(5, 0, Palette::Red)
		  rect.draw_inner_outer(0, 20, Palette::Green)
    end

    circle = Circle.new(350, 250, 200)
    sample_case("Circle Frame") do
		  circle.draw_inner_outer(5, 0);
		  circle.draw_inner_outer(0, 20, Palette::Brown);
    end

	  radian = Math.radians(45)
	  rect = Rect.new(150, 200, 400, 100)
    sample_case("Rotate") do
      rect.draw
      rect.rotated(radian).draw(Palette::Orange)
    end

	  line = LineString.new [
		  [ 50, 100 ],[ 600, 100 ],
		  [ 50, 200 ],[ 600, 200 ],
		  [ 50, 300 ],[ 600, 300 ],
		  [ 50, 400 ]
	  ]
    sample_case("Line String") do
      line.draw(3, Palette::Yellow)
    end

    sample_case("Arrow") do
      Line.new(50, 200, 200, 250).draw_arrow
      Line.new(250, 350, 500, 100).draw_arrow(5, [ 20, 50 ], Palette::Yellow)
    end

	  line = LineString.new [
		  [ 50, 50 ],[ 200, 200 ],
		  [ 400, 200 ],[ 100, 400 ],
		  [ 500, 400 ]
	  ]
    sample_case("Spline") do
      line.draw_catmull_rom(8)
    end
  end
end

while System.update do
  fiber.resume
end
