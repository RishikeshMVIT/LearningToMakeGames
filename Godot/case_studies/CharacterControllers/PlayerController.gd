class_name CharacterController
extends CharacterBody3D

const SPEED = 5.0
const JUMP_VELOCITY = 4.5

# Get the gravity from the project settings to be synced with RigidBody nodes.
var gravity: float = ProjectSettings.get_setting("physics/3d/default_gravity")

@export_category("Camera")
@export var mouse_sensitivity: float = 0.1
@export var pitch_lower_limit: float = deg_to_rad(-90.0)
@export var pitch_upper_limit: float = deg_to_rad(90.0)

@onready var head_joint: Node3D = $HeadJoint
@onready var camera: Camera3D = $HeadJoint/Camera3D

var _mouse_input:bool = false
var _pitch_input:float
var _yaw_input:float
var _mouse_rotation:Vector3


func _ready() -> void:
	Input.mouse_mode = Input.MOUSE_MODE_CAPTURED

func _unhandled_input(event: InputEvent) -> void:
	_mouse_input = (event is InputEventMouseMotion) and (Input.get_mouse_mode() == Input.MOUSE_MODE_CAPTURED)
	if (_mouse_input):
		_pitch_input = -event.relative.y * mouse_sensitivity
		_yaw_input = -event.relative.x * mouse_sensitivity

func _physics_process(delta: float) -> void:
	# Mouse Input
	_update_camera(delta)

	# Add the gravity.
	if not is_on_floor():
		velocity.y -= gravity * delta

	# Handle jump.
	if Input.is_action_just_pressed("ui_accept") and is_on_floor():
		velocity.y = JUMP_VELOCITY

	# Get the input direction and handle the movement/deceleration.
	# As good practice, you should replace UI actions with custom gameplay actions.
	var input_dir := Input.get_vector("action_move_left","action_move_right","action_move_forward","action_move_backward")
	var direction := (transform.basis * Vector3(input_dir.x, 0, input_dir.y)).normalized()
	if direction:
		velocity.x = direction.x * SPEED
		velocity.z = direction.z * SPEED
	else:
		velocity.x = move_toward(velocity.x, 0, SPEED)
		velocity.z = move_toward(velocity.z, 0, SPEED)

	move_and_slide()
	

func _update_camera(delta: float) -> void:
	_mouse_rotation.x += _pitch_input * delta
	_mouse_rotation.x = clamp(_mouse_rotation.x, pitch_lower_limit, pitch_upper_limit)
	_mouse_rotation.y += _yaw_input * delta

	# Rotate Player
	global_transform.basis = Basis.from_euler(Vector3(0.0, _mouse_rotation.y, 0.0))

	# Rotate Camera
	head_joint.transform.basis = Basis.from_euler(Vector3(_mouse_rotation.x, 0.0, 0.0))
	camera.rotation.z = 0.0

	_pitch_input = 0.0
	_yaw_input = 0.0
