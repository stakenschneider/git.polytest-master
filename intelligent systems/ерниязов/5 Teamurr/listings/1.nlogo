globals [ max-sheep ]  ; don't let sheep population grow too large
; Sheep and wolves are both breeds of turtle.
breed [ sheep a-sheep ]  ; sheep is its own plural, so we use "a-sheep" as the singular.
breed [ wolves wolf ]
turtles-own [ energy ]       ; both wolves and sheep have energy
patches-own [ countdown ]

to setup
  clear-all
  ifelse netlogo-web? [set max-sheep 10000] [set max-sheep 30000]

  ; Check model-version switch
  ; if we're not modeling grass, then the sheep don't need to eat to survive
  ; otherwise the grass's state of growth and growing logic need to be set up
  ifelse model-version = "sheep-wolves-grass" [
    ask patches [
      set pcolor one-of [ green brown ]
      ifelse pcolor = green
        [ set countdown grass-regrowth-time ]
      [ set countdown random grass-regrowth-time ] ; initialize grass regrowth clocks randomly for brown patches
    ]
  ]
  [
    ask patches [ set pcolor green ]
  ]

  create-sheep initial-number-sheep  ; create the sheep, then initialize their variables
  [
    set shape  "sheep"
    set color white
    set size 1.5  ; easier to see
    set label-color blue - 2
    set energy random (2 * sheep-gain-from-food)
    setxy random-xcor random-ycor
  ]

  create-wolves initial-number-wolves  ; create the wolves, then initialize their variables
  [
    set shape "wolf"
    set color black
    set size 2  ; easier to see
    set energy random (2 * wolf-gain-from-food)
    setxy random-xcor random-ycor
  ]
  display-labels
  reset-ticks
end