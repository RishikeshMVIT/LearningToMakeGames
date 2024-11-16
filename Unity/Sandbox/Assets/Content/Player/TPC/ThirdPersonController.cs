// Copyright (c) Sandbox 2024. All rights reserved

using UnityEngine;
using UnityEngine.InputSystem;

namespace Sandbox
{
    /// <summary>
    /// ThirdPersonController
    /// </summary>
    

    [RequireComponent(typeof(CharacterController))]
    public class ThirdPersonController : MonoBehaviour
    {
        void Start()
        {
        
        }

        void Update()
        {

        }


        private CharacterController controller;

        [SerializeField]
        private InputAction moveAction;

    }
}
