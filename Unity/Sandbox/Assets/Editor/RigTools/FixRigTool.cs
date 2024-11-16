// Copyright (c) Sandbox 2024. All rights reserved

using UnityEngine;
using UnityEditor;

namespace Sandbox
{
    /// <summary>
    /// FixRigTool
    /// </summary>
    public class FixRigTool
    {
        [MenuItem("Assets/Tools/Rig/Fix Legacy Rig")]
        [MenuItem("Tools/Rig/Fix Legacy Rig")]
        public static void FixRigToolMenuOption()
        {
            if (Selection.assetGUIDs.Length > 0)
            {
                foreach (var asset in Selection.assetGUIDs)
                {
                    string assetPath = AssetDatabase.GUIDToAssetPath(asset);

                    //Change Rig Type
                    ModelImporter modelImporter = ModelImporter.GetAtPath(assetPath) as ModelImporter;
                    modelImporter.animationType = ModelImporterAnimationType.Generic;

                    //Apply changes
                    AssetDatabase.WriteImportSettingsIfDirty(assetPath);
                    AssetDatabase.ImportAsset(assetPath, ImportAssetOptions.ForceUpdate);
                }
            }
        }

        [MenuItem("Assets/Tools/Rig/Fix Legacy Rig", validate = true)]
        [MenuItem("Tools/Rig/Fix Legacy Rig", validate = true)]
        public static bool FixRigToolMenuOptionValidate()
        {
            if (Selection.assetGUIDs.Length == 0)
            {
                return false;
            }

            foreach (var asset in Selection.assetGUIDs)
            {
                string assetPath = AssetDatabase.GUIDToAssetPath(asset);
                ModelImporter modelImporter = ModelImporter.GetAtPath(assetPath) as ModelImporter;

                if (modelImporter == null)
                {
                    return false;
                }
            }

            return true;
        }
    }
}
