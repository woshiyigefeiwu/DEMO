--
-- DESCRIPTION
--
-- @COMPANY **
-- @AUTHOR **
-- @DATE ${date} ${time}
--

---@type WBP_GameStart_C
local WBP_GameStart = UnLua.Class()

local IsFirstTimes = true;

function WBP_GameStart:Construct()
    self:Bind() 
end

function WBP_GameStart:Bind()
    self.PlaceStageButton.OnClicked:Add(self, self.OnClickedPlace);
    self.StartStageButton.OnClicked:Add(self, self.OnClickedStart);

    local MyPawn = UE.UGameplayStatics.GetPlayerPawn(self,0);
    local MyPC = MyPawn:GetController();
    print("WBP_GameStart:Bind()");
    self:PauseGame();   -- ¿∂Õº£¨‘›Õ£”Œœ∑
end

----------------------------- Event -----------------------------

function WBP_GameStart:OnClickedPlace()
    -- print("OnClickedPlace")
    local MyPawn = UE.UGameplayStatics.GetPlayerPawn(self,0);
    local MyPC = MyPawn:GetController();
    if(MyPC) then
        MyPC:OnClick_PlaceButton();
    end
end

function WBP_GameStart:OnClickedStart()
    self:ReleaseGame();
    local MyPawn = UE.UGameplayStatics.GetPlayerPawn(self,0);
    local MyPC = MyPawn:GetController();
    if(MyPC) then
        MyPC:OnClick_GameStart();
    end
end




--function WBP_GameStart:Initialize(Initializer)
--end

--function WBP_GameStart:PreConstruct(IsDesignTime)
--end

--function WBP_GameStart:Tick(MyGeometry, InDeltaTime)
--end

return WBP_GameStart
