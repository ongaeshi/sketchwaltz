Graphics.set_background([11, 22, 33])
$font = Font.new(40)

def sample_case(title)
  is_pause = false
  rest = 90

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
    sample_case("Cursor Pos") do
      pos = Cursor.pos
      Circle.new(pos.x, pos.y, 15).draw Palette::Yellow
      $font[pos.to_s].draw
    end

    count = 0
    sample_case("Mouse Down") do
      count += 1 if MouseL.down
      count -= 1 if MouseR.down
      $font["#{count} times"].draw
    end

    count = 0
    sample_case("Mouse Pressed") do
      count += 1 if MouseL.pressed
      count -= 1 if MouseR.pressed
      $font["#{count} times"].draw
    end

    count = 0
    sample_case("Mouse Up") do
      count += 1 if MouseL.up
      count -= 1 if MouseR.up
      $font["#{count} times"].draw
    end

    pos = Point.new(200, 200)
    sample_case("Delta Speed") do
      delta = Cursor.delta
      pos = Point.new(pos.x + delta.x, pos.y + delta.y)
      # pos += delta
      Circle.new(pos.x, pos.y, 15).draw(Palette::Yellow)
      $font[delta.to_s].draw
    end

    pos = Point.new(200, 200)
    sample_case("Wheel") do
      y = Mouse.wheel
      x = Mouse.wheelh
      pos = Point.new(pos.x + x, pos.y + y)
      # pos.x += x
      # pos.y += y
      Rect.new(pos.x, pos.y, 100, 100).draw(Palette::Yellow)
    end

  end
end

while System.update do
  fiber.resume
end
