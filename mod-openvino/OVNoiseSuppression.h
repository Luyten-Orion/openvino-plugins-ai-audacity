// Copyright (C) 2023 Intel Corporation
// SPDX-License-Identifier: GPL-3.0-only

#pragma once

#include "effects/StatefulEffect.h"
#include <wx/weakref.h>

class WaveTrack;
class wxChoice;
class WaveChannel;
class wxCheckBox;
class wxSizer;

namespace ov
{
   class CompiledModel;
}

class EffectOVNoiseSuppression final : public StatefulEffect
{
public:

   static const ComponentInterfaceSymbol Symbol;

   EffectOVNoiseSuppression();
   virtual ~EffectOVNoiseSuppression();

   // ComponentInterface implementation
   ComponentInterfaceSymbol GetSymbol() const override;
   TranslatableString GetDescription() const override;
   VendorSymbol GetVendor() const override;

   // EffectDefinitionInterface implementation

   EffectType GetType() const override;
   bool IsInteractive() const override;

   bool Process(EffectInstance& instance, EffectSettings& settings) override;

   bool UpdateProgress(double perc);

   std::unique_ptr<EffectEditor> PopulateOrExchange(
      ShuttleGui& S, EffectInstance& instance,
      EffectSettingsAccess& access, const EffectOutputs* pOutputs) override;

   void OnAdvancedCheckboxChanged(wxCommandEvent& evt);

protected:

   wxChoice* mTypeChoiceDeviceCtrl;
   int m_deviceSelectionChoice = 0;

   wxChoice* mTypeChoiceModelCtrl;
   int m_modelSelectionChoice = 0;

private:

   enum control
   {
      ID_Type = 10000,
      ID_Type_Model,
      ID_Attn_Limit,
      ID_Type_AdvancedCheckbox
   };

   std::vector< std::string > mSupportedDevices;
   std::vector< EnumValueSymbol > mGuiDeviceSelections;

   std::vector< std::string > mSupportedModels;
   std::vector< EnumValueSymbol > mGuiModelSelections;

   wxCheckBox* mShowAdvancedOptionsCheckbox;
   void show_or_hide_advanced_options();
   bool mbAdvanced = false;

   // For little noise reduction, set to 6-12.
   // For medium, 18-24.
   // 100 means no attenuation limit
   float mAttenuationLimit = 100.0f;

   wxSizer* attentuationLimitSizer = nullptr;
   wxSizer* noAdvancedSettingsLabel = nullptr;

   wxWeakRef<wxWindow> mUIParent{};

   DECLARE_EVENT_TABLE()
};
