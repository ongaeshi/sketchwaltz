$font = Font.new(50)
texture = Texture.new("Example/Windmill.png")
not_existing_texture = Texture.new("NOT_EXIST_TEXTURE.png")

def sample_case(title)
  1.upto(60) do
    yield

    $font[title].draw(0, 380)

    Fiber.yield
  end
end

fiber = Fiber.new do
  loop do
    sample_case("Draw") do
      texture.draw
    end

    sample_case("Change Position") do
      texture.draw(100, 50)
    end

    sample_case("Draw a part") do
      texture[260, 100, 200, 220].draw(20, 20)
    end

    sample_case("Mirror") do
      texture.mirror.draw
      texture[260, 100, 200, 220].mirror.draw(350, 200)
    end

    sample_case("Flip") do
      texture.flip.draw
      texture[260, 100, 200, 220].flip.draw(350, 200)
    end

    sample_case("Scale") do
      texture.scale(0.5).draw
      texture.scale(1.0, 0.5).draw(0, 200)
      # 10.downto(1) do |e|
      #   texture[260, 100, 200, 220].scale(e * 0.1).draw(350, 200)
      # end
    end

    sample_case("Resize") do
      texture.resize(640, 480).draw
      # texture[260, 100, 200, 220].resize(50, 50).draw
    end

    # sample_case("Map") do
	  #   texture.map(640, 480).draw
    # end

    sample_case("Repeat") do
	    texture.repeat(640, 480).draw(0, 0)
    end

    sample_case("Rotate") do
      texture.rotate(Math.radians(-15)).draw()
      texture[260, 100, 200, 220].rotate(Math.radians(15)).draw(350, 200)
    end

    sample_case("Specicy Center") do
      texture.rotate_at(0, 0, Math.radians(-15)).draw()
	    texture[260, 100, 200, 220].rotate_at(50, 50, Math.radians(15)).draw(350, 200)
    end

    sample_case("Draw to rectangle") do
      Rect.new(100, 100, 300, 200)[texture].draw
    end

    sample_case("Draw a part") do
      Rect.new(100, 100, 300, 200)[texture[260, 100, 200, 220]].draw
    end

    sample_case("Rotated") do
      Rect.new(100, 100, 300, 200).rotated(Math.radians(45))[texture].draw
    end

    sample_case("Alpha") do
      Rect.new(0, 0, 300, 300).draw
      texture.draw(100, 100, [255, 255, 255, 180])
    end

    sample_case("Multiply color") do
      texture.draw(100, 100, [0, 255, 255])
    end

    sample_case("Width&Height") do
      Rect.new(0, 0, texture.width, texture.height).draw(Palette::Skyblue)
    end

    sample_case("Draw at") do
	    texture[260, 100, 200, 220].draw_at(300, 300)
    end

    sample_case("UV") do
	    texture.uv(0.0, 0.0, 0.5, 1.0).draw(100, 100)
    end

    sample_case("Not Existing") do
      not_existing_texture.draw
    end
  end
end

while System.update do
  fiber.resume
end
