extends Node3D

@export_category("Movement")
@export_range(0, 100.0, 1) var camera_move_speed: float = 20.0

@export_category("Zoom")
@export_range(0, 100.0, 1) var camera_zoom_speed: float = 20.0
@export_range(1, 100.0, 1) var camera_zoom_min: float = 10.0
@export_range(0, 100.0, 1) var camera_zoom_max: float = 25.0
@export_range(0, 2.0, 0.1) var camera_zoom_speed_damp: float = 0.9

@export_category("Pan")
@export_range(0, 64, 4) var camera_auto_pan_margin: int = 32
@export_range(0, 20.0, 0.5) var camera_auto_pan_speed: float = 20.0


@onready var camera_joint: Node3D = $CameraJoint
@onready var camera: Camera3D = $CameraJoint/RTSCamera

# Flags
var camera_can_process: bool = true
var camera_base_can_move: bool = true
var camera_can_zoom: bool = true
var camera_can_pan: bool = true

var camera_zoom_direction: float = 0.0



func _ready() -> void:
	Input.mouse_mode = Input.MOUSE_MODE_CONFINED_HIDDEN
	pass

func _process(delta: float) -> void:
	if (!camera_can_process): return

	camera_base_move(delta)
	camera_zoom_update(delta)
	camera_auto_pan(delta)

func _unhandled_input(event: InputEvent) -> void:
	# Camera Zoom
	if (event.is_action("camera_zoom_in")):
		camera_zoom_direction = -1.0
	elif (event.is_action("camera_zoom_out")):
		camera_zoom_direction = 1.0

func camera_base_move(delta: float) -> void:
	if (!camera_base_can_move) : return

	var input_direction: Vector2 = Input.get_vector("camera_left", "camera_right", "camera_forward", "camera_backward").normalized()

	position.x += input_direction.x * delta * camera_move_speed
	position.z += input_direction.y * delta * camera_move_speed

func camera_zoom_update(delta: float) -> void:
	if (!camera_can_zoom): return

	var zoom: float = clamp(camera.position.z + camera_zoom_speed * camera_zoom_direction * delta, camera_zoom_min, camera_zoom_max)
	camera.position.z = clamp(zoom, camera_zoom_min, camera_zoom_max)

	camera_zoom_direction *= camera_zoom_speed_damp

func camera_auto_pan(delta: float) -> void:
	if(!camera_can_pan): return

	var current_viewport: Viewport = get_viewport()
	var pan_direction: Vector2 = Vector2(0, 0)
	var viewport_visible_rect: Rect2i = Rect2i(current_viewport.get_visible_rect())
	var viewport_size: Vector2 = viewport_visible_rect.size
	var current_mouse_pos: Vector2 = current_viewport.get_mouse_position()
	var zoom_factor: float = camera.position.z * 0.1

	if (current_mouse_pos.x < camera_auto_pan_margin) or (current_mouse_pos.x > (viewport_size.x - camera_auto_pan_margin)):
		if (current_mouse_pos.x > viewport_size.x/2): pan_direction.x = 1
		elif (current_mouse_pos.x < viewport_size.x/2): pan_direction.x = -1
		translate(Vector3(pan_direction.x * delta * camera_auto_pan_speed * zoom_factor, 0, 0))

	if (current_mouse_pos.y < camera_auto_pan_margin) or (current_mouse_pos.y > (viewport_size.y - camera_auto_pan_margin)):
		if (current_mouse_pos.y > viewport_size.y/2): pan_direction.y = 1
		elif (current_mouse_pos.y < viewport_size.y/2): pan_direction.y = -1
		translate(Vector3(0, 0, pan_direction.y * delta * camera_auto_pan_speed * zoom_factor))

