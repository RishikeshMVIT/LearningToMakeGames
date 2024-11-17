extends CharacterBody3D

@export_category("Camera")
@export var TILT_LOWER_LIMIT : float = deg_to_rad(-90.0)
@export var TILT_UPPER_LIMIT : float = deg_to_rad(90.0)
@export var MOUSE_SENSITIVITY : float = 0.1

@export_range(1, 10, 0.1) var CROUCH_SPEED : float = 2.0

@onready var camera_joint: Node3D = $CameraJoint
@onready var animation_player: AnimationPlayer = $AnimationPlayer

const SPEED = 5.0
const JUMP_VELOCITY = 4.5

var _is_mouse_moving : bool = false
var _input_rotation : float = 0.0
var _input_tilt : float = 0.0
var _mouse_rotation : Vector3 = Vector3.ZERO
var _camera_rotation : Vector3 = Vector3.ZERO
var _player_rotation : Vector3 = Vector3.ZERO

var _is_crouching : bool = false

func _update_camera(delta: float) -> void:
	_mouse_rotation.x += _input_tilt * delta
	_mouse_rotation.x = clamp(_mouse_rotation.x, TILT_LOWER_LIMIT, TILT_UPPER_LIMIT)
	_mouse_rotation.y += _input_rotation * delta
	
	_player_rotation = Vector3(0.0, _mouse_rotation.y, 0.0)
	_camera_rotation = Vector3(_mouse_rotation.x, 0.0, 0.0)
	
	camera_joint.transform.basis = Basis.from_euler(_camera_rotation)
	camera_joint.rotation.z = 0.0
	
	global_transform.basis = Basis.from_euler(_player_rotation)
	
	_input_rotation = 0.0
	_input_tilt = 0.0

func _toggle_crouch() -> void:
	if _is_crouching:
		animation_player.play("Crouch", -1, -CROUCH_SPEED, true)
	else:
		animation_player.play("Crouch", -1, CROUCH_SPEED)
	
	_is_crouching = not _is_crouching

func _ready() -> void:
	Input.mouse_mode = Input.MOUSE_MODE_CAPTURED

func _unhandled_input(event: InputEvent) -> void:
	_is_mouse_moving = event is InputEventMouseMotion and Input.get_mouse_mode() == Input.MOUSE_MODE_CAPTURED
	if _is_mouse_moving:
		_input_rotation = -event.relative.x * MOUSE_SENSITIVITY
		_input_tilt = -event.relative.y * MOUSE_SENSITIVITY
	
	if event.is_action_pressed("action_crouch"):
		_toggle_crouch()

func _physics_process(delta: float) -> void:
	if not is_on_floor():
		velocity += get_gravity() * delta

	# Handle jump.
	if Input.is_action_just_pressed("ui_accept") and is_on_floor():
		velocity.y = JUMP_VELOCITY
	
	_update_camera(delta)
	
	var input_dir := Input.get_vector("move_left", "move_right", "move_forward", "move_backward")
	var direction := (transform.basis * Vector3(input_dir.x, 0, input_dir.y)).normalized()
	if direction:
		velocity.x = direction.x * SPEED
		velocity.z = direction.z * SPEED
	else:
		velocity.x = move_toward(velocity.x, 0, SPEED)
		velocity.z = move_toward(velocity.z, 0, SPEED)

	move_and_slide()
