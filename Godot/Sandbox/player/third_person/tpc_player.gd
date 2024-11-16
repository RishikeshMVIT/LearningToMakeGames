class_name Player
extends CharacterBody3D

@export var jump_velocity : float = 100
@export var move_speed : float = 100

@export var mouse_sensitivity : float :
	get:
		return mouse_sensitivity
	set(value):
		mouse_sensitivity = value/1000

@onready var camera_joint: Node3D = $CameraJoint
@onready var camera: Camera3D = $CameraJoint/SpringArm3D/Camera3D

var gravity : float = ProjectSettings.get_setting("physics/3d/default_gravity")

func _enter_tree() -> void:
	set_multiplayer_authority(name.to_int())

func _ready() -> void:
	Input.mouse_mode = Input.MOUSE_MODE_CAPTURED
	camera.current = is_multiplayer_authority()

func _input(event: InputEvent) -> void:
	if event is InputEventMouseMotion:
		rotate_y(-event.relative.x * mouse_sensitivity)
		camera_joint.rotate_x(-event.relative.y * mouse_sensitivity)
		camera_joint.rotation.x = clamp(camera_joint.rotation.x, -1.570796, 0.5)

func _physics_process(delta: float) -> void:
	if not is_on_floor():
		velocity.y -= gravity * delta
	
	if Input.is_action_just_pressed("action_jump") and is_on_floor():
		velocity.y = jump_velocity
	
	var input_direction = Input.get_vector("move_left", "move_right", "move_forward", "move_backward")
	var move_direction = (transform.basis * Vector3(input_direction.x, 0, input_direction.y)).normalized()
	
	if move_direction:
		velocity.x = move_direction.x * move_speed
		velocity.z = move_direction.z * move_speed
	else:
		velocity.x = move_toward(velocity.x, 0, move_speed)
		velocity.z = move_toward(velocity.z, 0, move_speed)
	
	move_and_slide()
