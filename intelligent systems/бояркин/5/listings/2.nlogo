to go
  ; stop the simulation of no wolves or sheep
  if not any? turtles [ stop ]
  ; stop the model if there are no wolves and the number of sheep gets very large
  if not any? wolves and count sheep > max-sheep [ user-message "The sheep have inherited the earth" stop ]
  ask sheep [
    move
    if model-version = "sheep-wolves-grass" [ ; in this version, sheep eat grass, grass grows and it costs sheep energy to move
      set energy energy - 1  ; deduct energy for sheep only if running sheep-wolf-grass model version
      eat-grass  ; sheep eat grass only if running sheep-wolf-grass model version
      death ; sheep die from starvation only if running sheep-wolf-grass model version
    ]
    reproduce-sheep  ; sheep reproduce at random rate governed by slider
  ]
  ask wolves [
    move
    set energy energy - 1  ; wolves lose energy as they move
    eat-sheep ; wolves eat a sheep on their patch
    death ; wolves die if our of energy
    reproduce-wolves ; wolves reproduce at random rate governed by slider
  ]
  if model-version = "sheep-wolves-grass" [ ask patches [ grow-grass ] ]
  ; set grass count patches with [pcolor = green]
  tick
  display-labels
end