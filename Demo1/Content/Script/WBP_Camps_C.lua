--
-- DESCRIPTION
--
-- @COMPANY **
-- @AUTHOR **
-- @DATE ${date} ${time}
--

---@type WBP_Camps_C
local WBP_Camps = UnLua.Class()

-- Э��
local function run(self)
    UE.UKismetSystemLibrary.Delay(self, 0.5) -- �ӳ�һ��
    self:Bind()
end

function WBP_Camps:Construct()
    coroutine.resume(coroutine.create(run),self)
end

function WBP_Camps:Bind()
    self.CampButton.OnClicked:Add(self, self.OnClickedCampButton);
end

function WBP_Camps:InitInfo(name, image)

end

------------------------- Event -----------------------------

function WBP_Camps:OnClickedCampButton()
    local MyPawn = UE.UGameplayStatics.GetPlayerPawn(self,0);
    local MyPC = MyPawn:GetController();
    if(MyPC) then
        MyPC:OnClick_SelectButton();
    end

    -- ��������ǵû���Ҫ�� GameState ��һ�� Camp_Target�����ں�������AI��ʱ��ͳ������
end


--function WBP_Camps:Initialize(Initializer)
--end

--function WBP_Camps:PreConstruct(IsDesignTime)
--end

--function WBP_Camps:Tick(MyGeometry, InDeltaTime)
--end

return WBP_Camps
