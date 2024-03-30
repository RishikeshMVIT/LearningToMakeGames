extends Node2D

@export var debug_enable: bool = false
var debug: Dictionary = {}

func steer(
	velocity: Vector2,
	global_pos: Vector2,
	target_pos: Vector2,
	max_speed: float = 200.0,
	max_rotation: float = 50.0
) -> Vector2:

	var direction: Vector2 = target_pos - global_pos
	var desired_velocity: Vector2 = direction.normalized() * max_speed

	var steering: Vector2 = (direction - velocity) / max_rotation

	if (debug_enable):
		update_debug({
			"velocity": velocity,
			"desired_velocity": desired_velocity,
			"steering": steering
		})

	return velocity + steering

func update_debug(dict):
	for key in dict:
		debug[key] = dict[key]

func _process(delta: float) -> void:
	queue_redraw()

func _draw() -> void:
	if not debug_enable:
		return

	draw_circle(position, 50.0, Color.GREEN)
	draw_circle(get_local_mouse_position(), 20.0, Color.RED)
	draw_line(position, debug["velocity"], Color.BLUE, 4.0)
	draw_line(position, debug["desired_velocity"], Color.GRAY, 4.0)
	draw_line(debug["velocity"], debug["desired_velocity"], Color.YELLOW, 4.0)
