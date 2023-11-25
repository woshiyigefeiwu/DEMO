--
-- DESCRIPTION
--
-- @COMPANY **
-- @AUTHOR **
-- @DATE ${date} ${time}
--

---@type WBP_Soldiers_C
local WBP_Soldiers = UnLua.Class()

-- function WBP_Soldiers:Construct()
-- end

function WBP_Soldiers:InitInfo(SoldierInfo)

    self.Overridden.InitInfo(self,SoldierInfo);

    -- œ‘ æ“ªœ¬Õº∆¨
    local image = self:GetImage();
    if(image) then
        local imgobj = UE4.LoadObject(image)
        self.SoliderImage:SetBrushfromTexture(imgobj)
    end
end


--function WBP_Soldiers:Initialize(Initializer)
--end

--function WBP_Soldiers:PreConstruct(IsDesignTime)
--end

--function WBP_Soldiers:Tick(MyGeometry, InDeltaTime)
--end

return WBP_Soldiers
