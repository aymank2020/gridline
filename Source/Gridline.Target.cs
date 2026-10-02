using UnrealBuildTool;
public class GridlineTarget : TargetRules {
    public GridlineTarget(TargetInfo Target) : base(Target) {
        Type = TargetType.Game;
        DefaultBuildSettings = BuildSettingsVersion.V5;
        ExtraModuleNames.Add("Gridline");
    }
}
