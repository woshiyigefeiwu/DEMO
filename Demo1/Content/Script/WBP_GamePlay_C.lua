--
-- DESCRIPTION
--
-- @COMPANY **
-- @AUTHOR **
-- @DATE ${date} ${time}
--

---@type WBP_GamePlay_C
local WBP_GamePlay = UnLua.Class()

local IsFirstTimes = true;

function WBP_GamePlay:Construct()
    self:Bind()
    self:Init()
end

function WBP_GamePlay:Bind()
    self.PauseButton.OnClicked:Add(self, self.OnClickedPauseButton);
    self.ContinueButton.OnClicked:Add(self, self.OnClickedContinueButton);
    self.RestartButton.OnClicked:Add(self, self.OnClickedRestartButton);
    self.ExitButton.OnClicked:Add(self, self.OnClickedExitButton);
    self.GameDataButton.OnClicked:Add(self,self.OnClickedGameDataButton);

    local GS = UE.UGameplayStatics.GetGameState(self);
    GS.GameOverDelegate:Add(self,self.OnGameOver);
end

function WBP_GamePlay:Init()
    self:SetUIVisible(self.ButtonList,false);
    self:SetUIVisible(self.GameData, true);

    -- ��ʼ��һ����Ӫ���ݰ�ť
    local GS = UE.UGameplayStatics.GetGameState(self);
    local CampInfoList = GS:GetCampInfoList();

    self.GameData:ClearChildren()
    for i=1,CampInfoList:Length() do
        local CampSubUIClass = UE.UClass.Load("/Game/Demo/BluePrints/UI/WBP_GameData_Camp.WBP_GameData_Camp_C")    -- ע��·��
        local CampSubUI = NewObject(CampSubUIClass, self);
        
        self.GameData:AddChild(CampSubUI);
        CampSubUI:InitInfo(CampInfoList[i]);   -- ��ʼ��һ�°�ť����ʽ�Լ���Ӫ��Ϣ
    end
end

------------------------- Event -------------------------

-- ��Ϸ����
function WBP_GamePlay:OnGameOver()
    -- self:QuitGame();
    local GS = UE.UGameplayStatics.GetGameState(self);
    local UIM = GS:GetUIManager();
    if(UIM) then
        UIM:ShowUI("UI_GameOver");
    end    
end

-- �˳���ť
function WBP_GamePlay:OnClickedExitButton()
    self:QuitGame();
end

-- ��ͣ��ť
function WBP_GamePlay:OnClickedPauseButton()
    self:PauseGame();   -- ��ͼ����ͣ��Ϸ
    self:SetUIVisible(self.ButtonList,true);
    self:SetUIVisible(self.PauseButton,false);
    self:SetUIVisible(self.GameDataButton,false);
    self:SetUIVisible(self.GameData,false);
end

-- ������ť
function WBP_GamePlay:OnClickedContinueButton()
    self:ReleaseGame(); -- ��ͼ��������Ϸ
    self:SetUIVisible(self.ButtonList,false);
    self:SetUIVisible(self.PauseButton,true);
    self:SetUIVisible(self.GameDataButton,true);
end

-- ���¿�ʼ��ť
function WBP_GamePlay:OnClickedRestartButton()
    self:RestartGame();
end

-- ����չʾ��ť
function WBP_GamePlay:OnClickedGameDataButton()
    self:ReverseUI(self.GameData);
end

------------------- �������� -----------------

-- ���� UI ����ʾ����
function WBP_GamePlay:SetUIVisible(UI, flag)
    if(flag) then
        if(UI:IsVisible() == false) then
            UI:SetVisibility(UE.ESlateVisibility.Visible)
        end
    else
        if(UI:IsVisible()) then
            UI:SetVisibility(UE.ESlateVisibility.Collapsed)
        end
    end
end

-- ��ת UI ����ʾ->���أ�����->��ʾ
function WBP_GamePlay:ReverseUI(UI)
    if(UI:IsVisible()) then
        UI:SetVisibility(UE.ESlateVisibility.Collapsed)
    else
        UI:SetVisibility(UE.ESlateVisibility.Visible)
    end
end

--function WBP_GamePlay:Initialize(Initializer)
--end

--function WBP_GamePlay:PreConstruct(IsDesignTime)
--end

--function WBP_GamePlay:Tick(MyGeometry, InDeltaTime)
--end

return WBP_GamePlay
