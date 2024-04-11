extends CharacterBody2D

@export var target: Node2D
@export var max_speed: float = 50.0

func _physics_process(delta: float) -> void:
	var direction: Vector2 = target.global_position - global_position
	direction.normalized()

	if (direction.length() > 0.3):
		velocity = direction * max_speed * delta
	else:
		velocity = Vector2.ZERO

	move_and_slide()
	_draw()

func _draw() -> void:
	draw_line(Vector2.ZERO, velocity, Color.RED, 1.0)
	pass
