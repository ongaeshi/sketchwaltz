Max_r, Min_r = 40, 10
ColorMax = 255
MaxNum = 60
Width = Window.center.x * 2
Height = Window.center.y * 2

Rate = 0.3

class MyCircle
  def initialize
    renewal
    @y = random(Height)
  end

  def renewal
    @max_r = random(Max_r - Min_r) + Min_r
    @x =  random(Width)
    @y = -random(@max_r)
    @color = [random(ColorMax), random(ColorMax), random(ColorMax)]
    @fall_step = (1 + random * 3) * Rate
    @r = 1
    @r_step = (random * 0.2 + 0.8) * Rate
  end

  def paint
    Circle.new(@x, @y, @r).draw(@color)
    @y += @fall_step
    @r += @r_step
    @r_step *= -1 if @r > @max_r or @r < 1
    renewal if @y > Height + Max_r
    true
  end
end

Graphics.set_background(Palette::Black)

circles = []
MaxNum.times { circles << MyCircle.new }

while System.update do
  circles.each { |e| e.paint }
end
